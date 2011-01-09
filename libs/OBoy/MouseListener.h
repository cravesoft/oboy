#pragma once

#include "oboylib/CrtDbgInc.h"

#include "Mouse.h"

namespace oboy
{
	class MouseListener
	{
	public:

		MouseListener() {}
		virtual ~MouseListener() {}

		virtual void mouseMove(Mouse *mouse) = 0;
		virtual void mouseButtonDown(Mouse *mouse, Mouse::Button button, int clickCount) = 0;
		virtual void mouseButtonUp(Mouse *mouse, Mouse::Button button) = 0;
		virtual void mouseWheel(Mouse *mouse, int wheelDelta) = 0;
		virtual void mouseEnter(Mouse *mouse) = 0;
		virtual void mouseLeave(Mouse *mouse) = 0;

	};
}

