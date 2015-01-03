#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "cinder/Rand.h"
#include "cinder/ImageIo.h"
#include "cinder/gl/Texture.h"
#include "cinder/Perlin.h"
#include "ParticleController.h"
#include "cinder/gl/TextureFont.h"


using namespace ci;
using namespace ci::app;
using namespace std;

class BasicAppApp : public AppNative {
  public:
	void setup();
	void mouseDown( MouseEvent event );	
	void keyDown( KeyEvent event);
	void update();
	void draw();
	void prepareSettings(Settings *settings);

	bool clear;
	ParticleController particleController;
};

void BasicAppApp::prepareSettings(Settings *settings)
{
	settings->setWindowSize(800, 600);
	settings->setFrameRate(60.0);
	settings->setFullScreen();
}

void BasicAppApp::setup()
{
	gl::enableAlphaBlending();
}

void BasicAppApp::mouseDown( MouseEvent event )
{
	particleController.addParticles(1);
}

void BasicAppApp::keyDown(KeyEvent event) {
	if (event.getChar() == 'c'){
		clear = !clear;
	}
	else if (event.getChar() == '1'){
		if (!particleController.wind.y){
			particleController.wind = Vec3f(ci::randFloat(-60.0, 60.0), ci::randFloat(-60.0, 60.0), true);
		}
		else{
			particleController.wind = Vec3f(0, 0, false);
		}
	}
	else if (event.getChar() == '2'){
		particleController.color += 1;
		if (particleController.color > 4){
			particleController.color = 1;
		}
	}
	else if (event.getChar() == '3'){
		particleController.addParticles(33);
	}

}

void BasicAppApp::update()
{
	particleController.update();
}

void BasicAppApp::draw()
{
	if (clear)
		gl::clear();
	particleController.draw();
}

CINDER_APP_NATIVE( BasicAppApp, RendererGl )