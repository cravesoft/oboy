#pragma once

#include "OBoyLib/CrtDbgInc.h"
#include "Graphics.h"
#include "Texturable.h"

namespace OBoy
{
  class Sphere : public Texturable
	{
	public:

    Sphere(float radius, unsigned int numSlices, unsigned int numStacks) {}
		virtual ~Sphere() {}

		virtual void setColor(OBoyLib::Color color) = 0;

    virtual bool build() = 0;

	};
}
