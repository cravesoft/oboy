#pragma once

#include "Sphere.h"
#include "LinuxShape.h"

namespace oboy
{
	class LinuxSphere : public LinuxShape, public Sphere
	{
	public:

		LinuxSphere(float radius, unsigned int numSlices, unsigned int numStacks);
    virtual ~LinuxSphere() {};

		virtual void setColor(oboylib::Color color);

    virtual bool build() { return LinuxShape::build(); };

    virtual void draw();

	};
};
