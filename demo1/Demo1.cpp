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
	oboy::Graphics *g = oboy::Environment::instance()->getGraphics();
	float w = (float)g->getWidth();
	float h = (float)g->getHeight();

	oboy::GamePad *pad = oboy::Environment::instance()->getGamePad(0);
	mPos = pad->getAnalogL();
	mPos.x() = w/2 + mPos.x()*w/2;
	mPos.y() = h/2 - mPos.y()*h/2;
}

void Demo1::draw(oboy::Graphics *g)
{
	g->setColor(0xFFFFFFFF);
	g->fillRect((int)mPos.x()-5,(int)mPos.y()-5,10,10);
}

void Demo1::handleGamePadAdded(int gamePadId)
{
	oboy::Environment::instance()->getGamePad(gamePadId)->addListener(this);
}

void Demo1::handleGamePadRemoved(int gamePadId)
{
	oboy::Environment::instance()->getGamePad(gamePadId)->removeListener(this);
}

void Demo1::gamePadButtonDown(oboy::GamePad *pad, oboy::GamePad::Button button)
{
	oboy::Environment::instance()->stopMainLoop();
}

void Demo1::gamePadButtonUp(oboy::GamePad *pad, oboy::GamePad::Button button)
{
}
