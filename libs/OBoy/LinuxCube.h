#pragma once

#include "LinuxShape.h"
#include "Cube.h"

namespace oboy
{
	class LinuxCube : public LinuxShape, public Cube
	{
	public:

		LinuxCube(float halfExtend);
    virtual ~LinuxCube() {};

    virtual void setColor(oboylib::Color color);

    virtual bool build() { return LinuxShape::build(); };

    virtual void draw();

	};
};
