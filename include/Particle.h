#pragma once
#include "cinder/Channel.h"
#include "cinder/Vector.h"
#include "cinder/Perlin.h"

#include <vector>

class Particle {
 public:
	Particle();
	Particle( ci::Vec2f );
	void update(ci::Vec3f);
	void draw(int);
	void wrap();
	
	ci::Vec2f	location;
	ci::Vec2f	orgLocation;
	ci::Vec2f	velocity;
	float		radius;
	float		perlinScale;
	float		speedScale;
	float		birthTime;
	float		shake;
	float		mass;
	int			typeID;
	int			sides;
	ci::Perlin	generator;
};