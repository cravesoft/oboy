#pragma once

#include "Sphere.h"
#include <GL/glus.h>
#include <GL/glew.h>

namespace OBoy
{
	class LinuxSphere : public Sphere
	{
	public:

		LinuxSphere(float radius, int numSlices, int numStacks);
		virtual ~LinuxSphere();

		virtual void setColor(Color color);

  private:
    
    GLUSshape mShape;
    GLuint mNumIndices;

	};
};
