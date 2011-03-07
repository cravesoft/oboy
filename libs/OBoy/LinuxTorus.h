#pragma once

#include "LinuxShape.h"
#include "Torus.h"

namespace OBoy
{
	class LinuxTorus : public LinuxShape, public Torus
	{
	public:

		LinuxTorus(float innerRadius, float outerRadius, unsigned int numSides, unsigned int numFaces);
    virtual ~LinuxTorus() {};

    virtual bool build() { return LinuxShape::build(); };

    virtual void draw();

	};
};
