#include "Explosion.h"

#include "OBoy/Environment.h"
#include "OBoy/ResourceManager.h"
#include "oboylib/OBoyUtil.h"

#define PARTICLE_MIN_SPEED 100.0f
#define PARTICLE_MAX_SPEED 200.0f

Explosion::Explosion(float x, float y, float radius)
{
	// initialize the particles:
	for (int i=0 ; i<NUM_PARTICLES ; i++)
	{
		mParticlePositions[i] = rotate(
			oboylib::Vector2(0, radius),
			randf(0,6.28f));
		mParticleVelocities[i] = 
			mParticlePositions[i].normalize() * randf(PARTICLE_MIN_SPEED, PARTICLE_MAX_SPEED);
		mParticlePositions[i].x() += x;
		mParticlePositions[i].y() += y;
	}

	mImage = oboy::Environment::getImage("IMAGE_BULLET");
	mStartTime = oboy::Environment::instance()->getTime();
	mDuration = 1.0f;
}

void Explosion::draw(oboy::Graphics *g)
{
  g->setColor(oboylib::Color(oboylib::Color::White));
	g->setColorizationEnabled(true); // required for alpha to affect rendering
	float alpha = 1 - (oboy::Environment::instance()->getTime() - mStartTime) / mDuration;
	g->setAlpha(alpha);
	g->setDrawMode(oboy::Graphics::DRAWMODE_ADDITIVE);

	for (int i=0 ; i<NUM_PARTICLES ; i++)
	{
		g->pushTransform();
			g->translate(
				mParticlePositions[i].x(),
				mParticlePositions[i].y());
			g->drawImage(mImage);
		g->popTransform();
	}

	g->setColorizationEnabled(false);
	g->setDrawMode(oboy::Graphics::DRAWMODE_NORMAL);
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
	return oboy::Environment::instance()->getTime() - mStartTime > mDuration;
}
