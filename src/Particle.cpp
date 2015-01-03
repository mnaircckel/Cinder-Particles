#include "Particle.h"
#include "cinder/Rand.h"
#include "cinder/gl/gl.h"
#include "cinder/app/AppBasic.h"

using namespace ci::app;
using namespace ci;

Particle::Particle()
{
}

Particle::Particle( Vec2f newLocation )
{
	location = newLocation;
	orgLocation = newLocation;
	velocity = Vec2f(5, 5);
	radius = ci::randFloat(1.5,8.0);
	mass = radius;
	perlinScale = ci::randFloat(0.015, 0.20);
	speedScale = ci::randFloat(5.5, 27.5);
	generator = Perlin();
	birthTime = getElapsedSeconds() + ci::randFloat(0, 100);
	shake = (float)ci::randInt(0,15)*ci::randInt(0,2);
	typeID = ci::randInt(1, 4);
	sides = ci::randInt(3, 14);
}

void Particle::update(Vec3f wind)
{
	// Noise is based on the location of where the particle was generted, as well as time Elapsed so each particle follows unique paths
	// The large the perlin scale, the quicker the particle "changes" paths/directions
	// The larger the speed scale, the faster the particle moves
	float noiseX =	generator.fBm(orgLocation.x*perlinScale + ci::randFloat(0,.25)*shake, (getElapsedSeconds()*perlinScale)) * speedScale;
	float noiseY = generator.fBm(orgLocation.y*perlinScale + ci::randFloat(0,.25)*shake, (getElapsedSeconds()*perlinScale)) * speedScale;
	velocity = Vec2f(noiseX,noiseY);
	velocity += Vec2f(wind.x/mass,wind.y/mass);
	location += velocity;
	Particle::wrap(); //Wrap around if the particle goes off the screen

}

void Particle::draw(int color)
{
	float tone = -.15;
	float wave = abs(radius*sin(getElapsedSeconds()-birthTime*perlinScale));
	switch (color) {
		case 1:
			gl::color(sin(velocity.x + velocity.y) + tone, cos(velocity.x + velocity.y) + tone, tan(velocity.y / velocity.x) + tone, 0.45);
			break;
		case 2:
			gl::color(Color(.05, .05, .75));
			break;
		case 3:
			gl::color(Color(1, 1, 1));
			break;
		case 4:
			gl::color(Color(1, 1, .25));
			break;
	}
	switch (typeID){
	case 1:
		gl::drawSolidCircle(location, wave + radius, sides);
		break;
	case 2:
		gl::drawCube(Vec3f(location.x, location.y, wave + radius + radius*shake*velocity.x*velocity.y), Vec3f(wave + radius, wave + radius, wave*2 - radius));
		break;
	case 3:
		gl::drawSphere(Vec3f(location.x, location.y, wave + radius), wave, sides);
		break;
	}

}

void Particle::wrap(){
	if (location.x > (float)getWindowWidth() + 2.0){
		location.x = -2.0;
	}
	else if (location.x < -2.0) {
		location.x = (float)getWindowWidth() + 2.0;
	}
	if (location.y >(float)getWindowHeight() + 2.0){
		location.y = -2.0;
	}
	else if (location.y < -2.0){
		location.y = (float)getWindowHeight() + 2.0;
	}
}
