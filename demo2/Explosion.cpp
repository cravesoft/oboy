#include "Explosion.h"

#include "OBoy/Environment.h"
#include "OBoy/ResourceManager.h"
#include "OBoyLib/OBoyUtil.h"

#define PARTICLE_MIN_SPEED 100.0f
#define PARTICLE_MAX_SPEED 200.0f

Explosion::Explosion(float x, float y, float radius)
{
	// initialize the particles:
	for (int i=0 ; i<NUM_PARTICLES ; i++)
	{
		mParticlePositions[i] = rotate(
			OBoyLib::Vector2(0, radius),
			randf(0,6.28f));
		mParticleVelocities[i] = 
			mParticlePositions[i].normalize() * randf(PARTICLE_MIN_SPEED, PARTICLE_MAX_SPEED);
		mParticlePositions[i].x += x;
		mParticlePositions[i].y += y;
	}

	mImage = OBoy::Environment::getImage("IMAGE_BULLET");
	mStartTime = OBoy::Environment::instance()->getTime();
	mDuration = 1.0f;
}

void Explosion::draw(OBoy::Graphics *g)
{
	g->setColor(0xFFFFFFFF);
	g->setColorizationEnabled(true); // required for alpha to affect rendering
	float alpha = 1 - (OBoy::Environment::instance()->getTime() - mStartTime) / mDuration;
	g->setAlpha(alpha);
	g->setDrawMode(OBoy::Graphics::DRAWMODE_ADDITIVE);

	for (int i=0 ; i<NUM_PARTICLES ; i++)
	{
		g->pushTransform();
			g->translate(
				mParticlePositions[i].x,
				mParticlePositions[i].y);
			g->drawImage(mImage);
		g->popTransform();
	}

	g->setColorizationEnabled(false);
	g->setDrawMode(OBoy::Graphics::DRAWMODE_NORMAL);
}

void Explosion::update(float dt)
{
	// move particles:
	for (int i=0 ; i<NUM_PARTICLES ; i++)
	{
		mParticlePositions[i] += mParticleVelocities[i] * dt;
		mParticleVelocities[i] *= 1 - (2.7f * dt);
	}
}

bool Explosion::isOver()
{
	return OBoy::Environment::instance()->getTime() - mStartTime > mDuration;
}
