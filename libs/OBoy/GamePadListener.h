#pragma once

#include "oboylib/CrtDbgInc.h"
#include "GamePad.h"
#include "Mouse.h"

namespace oboy
{

	class GamePadListener
	{
	public:

		GamePadListener() {}
		virtual ~GamePadListener() {}

		virtual void gamePadButtonDown(GamePad *pad, GamePad::Button button) = 0;
		virtual void gamePadButtonUp(GamePad *pad, GamePad::Button button) = 0;

	};
}

