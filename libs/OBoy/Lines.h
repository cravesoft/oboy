#pragma once

#include "OBoyLib/CrtDbgInc.h"
#include "Graphics.h"

namespace OBoy
{
	class Lines
	{
	public:

		Lines() {}
		virtual ~Lines() {}

		virtual void setColor(OBoyLib::Color color) = 0;

		virtual void setVertPos(int i, float x, float y, float z=0) = 0;
		virtual void setVertColor(int i, OBoyLib::Color color) = 0;

    virtual bool build() = 0;
	};
}
