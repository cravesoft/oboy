#pragma once

#include "LinuxShape.h"

namespace OBoy
{
	class LinuxPlane : public LinuxShape
	{
	public:

		LinuxPlane(float halfExtend);
    virtual ~LinuxPlane() {};

    virtual bool build() { return LinuxShape::build(); };

    virtual void draw();

	};
};
