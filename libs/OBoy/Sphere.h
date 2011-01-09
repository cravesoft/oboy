#pragma once

#include "oboylib/CrtDbgInc.h"
#include "Graphics.h"
#include "Texturable.h"

namespace oboy
{
  class Sphere : public Texturable
	{
	public:

    Sphere(float radius, unsigned int numSlices, unsigned int numStacks) {}
		virtual ~Sphere() {}

		virtual void setColor(Color color) = 0;

    virtual bool build() = 0;

	};
}
