#pragma once

#include "OBoy/Game.h"
#include "OBoy/GamePadListener.h"
#include "oboylib/Vector2.h"

class Demo1: public oboy::Game, public oboy::GamePadListener
{
public:

	Demo1();
	virtual ~Demo1();

	// singleton:
	static Demo1 *instance();
	static void destroy();

	// implementation of Game:
	virtual void update(float dt);
	virtual void draw(oboy::Graphics *g);
	virtual void handleGamePadAdded(int gamePadId);
	virtual void handleGamePadRemoved(int gamePadId);

	// implementation of GamePadListener:
	virtual void gamePadButtonDown(oboy::GamePad *pad, oboy::GamePad::Button button);
	virtual void gamePadButtonUp(oboy::GamePad *pad, oboy::GamePad::Button button);

private:

	static Demo1 *gInstance;

	oboylib::Vector2 mPos;

};
