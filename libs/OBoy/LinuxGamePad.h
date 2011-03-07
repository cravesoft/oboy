#pragma once

#include "GamePad.h"
#include <windows.h>
#include <XInput.h>

#pragma comment(lib, "XInput.lib")

namespace OBoy
{
	class LinuxGamePad : public GamePad
	{
	public:

		LinuxGamePad(int id);
		virtual ~LinuxGamePad();

		void vibrate(int leftVal=0, int rightVal=0);
	};
}
