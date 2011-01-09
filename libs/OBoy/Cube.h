#pragma once

#include "oboylib/CrtDbgInc.h"
#include "Graphics.h"
#include "Texturable.h"

namespace oboy
{
  class Cube : public Texturable
	{
	public:

    Cube(float halfExtent) {}
		virtual ~Cube() {}

		virtual void setColor(Color color) = 0;

    virtual bool build() = 0;

	};
}
