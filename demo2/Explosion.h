#pragma once

#include "OBoy/Graphics.h"
#include "oboylib/Vector2.h"

#define NUM_PARTICLES 20

class Explosion 
{
public:

	Explosion(float x, float y, float radius);

	bool isOver();
	void draw(oboy::Graphics *g);
	void update(float dt);

public:

	oboy::Image *mImage;
	float mStartTime;
	float mDuration;

	oboylib::Vector2 mParticlePositions[NUM_PARTICLES];
	oboylib::Vector2 mParticleVelocities[NUM_PARTICLES];

};

