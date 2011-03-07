#pragma once

#include "OBoyLib/CrtDbgInc.h"
#include "Graphics.h"
#include "Texturable.h"

namespace OBoy
{
  class Cube : public Texturable
	{
	public:

    Cube(float halfExtent) {}
		virtual ~Cube() {}

		virtual void setColor(OBoyLib::Color color) = 0;

    virtual bool build() = 0;

	};
}
