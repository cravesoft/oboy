#pragma once

#include "OBoy/Environment.h"
#include "OBoy/Game.h"
#include "OBoy/Graphics.h"
#include "OBoy/KeyboardListener.h"
#include "OBoyLib/OBoyUtil.h"
#include "OBoyLib/Vector2.h"

enum BodyType
{
	SMALL_ASTEROID = 0,
	BIG_ASTEROID = 1,
	MEDIUM_ASTEROID = 2,
	SHIP = 3,
	BULLET = 4
};


class Body 
{
public:

	Body(BodyType type, float posx=0, float posy=0, float velx=0, float vely=0);

	bool collidesWith(Body *body);
	void draw(OBoy::Graphics *g);
	void update(float dt);

private:
	void _draw(OBoy::Graphics *g, OBoyLib::Vector2 &pos);

public:
	OBoy::Image *mImage;
	OBoyLib::Vector2 mPos;
	OBoyLib::Vector2 mVel;
	float mRot;
	float mRotVel;
	float mRadius;
	float mTimeOfDeath;

	BodyType mType;
};

