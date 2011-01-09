#pragma once

#include "OBoy/Environment.h"
#include "OBoy/Game.h"
#include "OBoy/Graphics.h"
#include "OBoy/KeyboardListener.h"
#include "oboylib/OBoyUtil.h"
#include "oboylib/Vector2.h"

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
	void draw(oboy::Graphics *g);
	void update(float dt);

private:
	void _draw(oboy::Graphics *g, oboylib::Vector2 &pos);

public:
	oboy::Image *mImage;
	oboylib::Vector2 mPos;
	oboylib::Vector2 mVel;
	float mRot;
	float mRotVel;
	float mRadius;
	float mTimeOfDeath;

	BodyType mType;
};

