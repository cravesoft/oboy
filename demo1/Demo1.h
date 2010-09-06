#pragma once

#include "OBoy/Game.h"
#include "OBoy/GamePadListener.h"
#include "OBoyLib/Vector2.h"

class Demo1: public OBoy::Game, public OBoy::GamePadListener
{
public:

	Demo1();
	virtual ~Demo1();

	// singleton:
	static Demo1 *instance();
	static void destroy();

	// implementation of Game:
	virtual void update(float dt);
	virtual void draw(OBoy::Graphics *g);
	virtual void handleGamePadAdded(int gamePadId);
	virtual void handleGamePadRemoved(int gamePadId);

	// implementation of GamePadListener:
	virtual void gamePadButtonDown(OBoy::GamePad *pad, OBoy::GamePad::Button button);
	virtual void gamePadButtonUp(OBoy::GamePad *pad, OBoy::GamePad::Button button);

private:

	static Demo1 *gInstance;

	OBoyLib::Vector2 mPos;

};
