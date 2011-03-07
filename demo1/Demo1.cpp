#include "Demo1.h"

#include <assert.h>
#include "OBoy/Environment.h"
#include "OBoy/GamePad.h"
#include "OBoy/Graphics.h"
#include "OBoy/Mouse.h"
#include <string>

Demo1 *Demo1::gInstance = NULL;

Demo1::Demo1()
{
}

Demo1::~Demo1()
{
}

Demo1 *Demo1::instance()
{
	if (gInstance==NULL)
	{
		gInstance = new Demo1();
	}

	return gInstance;
}

void Demo1::destroy()
{
	assert(gInstance!=NULL);
	delete gInstance;
	gInstance = NULL;
}

void Demo1::update(float dt)
{
	OBoy::Graphics *g = OBoy::Environment::instance()->getGraphics();
	float w = (float)g->getWidth();
	float h = (float)g->getHeight();

	OBoy::GamePad *pad = OBoy::Environment::instance()->getGamePad(0);
	mPos = pad->getAnalogL();
	mPos.x() = w/2 + mPos.x()*w/2;
	mPos.y() = h/2 - mPos.y()*h/2;
}

void Demo1::draw(OBoy::Graphics *g)
{
  g->setColor(OBoyLib::Color(OBoyLib::Color::White));
	g->fillRect((int)mPos.x()-5,(int)mPos.y()-5,10,10);
}

void Demo1::handleGamePadAdded(int gamePadId)
{
	OBoy::Environment::instance()->getGamePad(gamePadId)->addListener(this);
}

void Demo1::handleGamePadRemoved(int gamePadId)
{
	OBoy::Environment::instance()->getGamePad(gamePadId)->removeListener(this);
}

void Demo1::gamePadButtonDown(OBoy::GamePad *pad, OBoy::GamePad::Button button)
{
	OBoy::Environment::instance()->stopMainLoop();
}

void Demo1::gamePadButtonUp(OBoy::GamePad *pad, OBoy::GamePad::Button button)
{
}
