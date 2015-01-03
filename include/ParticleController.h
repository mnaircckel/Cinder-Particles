#pragma once
#include "Particle.h"
#include "cinder/Vector.h"
#include <vector>
#include <list>

class ParticleController {
 public:
	ParticleController();
	void update();
	void draw();
	void addParticles( int amt );

	ci::Vec3f	 wind;
	int		color;

	std::list<Particle>	mParticles;
};