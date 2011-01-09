#pragma once

#include "oboylib/CrtDbgInc.h"
#include "Graphics.h"
#include "Texturable.h"

namespace oboy
{
  class Torus : public Texturable
	{
	public:

    Torus(float innerRadius, float outerRadius, unsigned int numSides, unsigned int numFaces) {}
		virtual ~Torus() {}

		virtual void setColor(Color color) = 0;

    virtual bool build() = 0;

	};
}
