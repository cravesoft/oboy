#pragma once

#include "OBoy/Graphics.h"
#include "OBoyLib/Vector2.h"

#define NUM_PARTICLES 20

class Explosion 
{
public:

	Explosion(float x, float y, float radius);

	bool isOver();
	void draw(OBoy::Graphics *g);
	void update(float dt);

public:

	OBoy::Image *mImage;
	float mStartTime;
	float mDuration;

	OBoyLib::Vector2 mParticlePositions[NUM_PARTICLES];
	OBoyLib::Vector2 mParticleVelocities[NUM_PARTICLES];

};

