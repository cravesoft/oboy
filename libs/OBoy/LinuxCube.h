#pragma once

#include "LinuxShape.h"
#include "Cube.h"

namespace OBoy
{
	class LinuxCube : public LinuxShape, public Cube
	{
	public:

		LinuxCube(float halfExtend);
    virtual ~LinuxCube() {};

    virtual void setColor(OBoyLib::Color color);

    virtual bool build() { return LinuxShape::build(); };

    virtual void draw();

	};
};
