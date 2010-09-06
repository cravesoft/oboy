#pragma once

#include "TriStrip.h"
#include <GL/glus.h>
#include <GL/glew.h>

namespace OBoy
{
	class LinuxTriStrip : public TriStrip
	{
	public:

		LinuxTriStrip(int numVerts);
		virtual ~LinuxTriStrip();

		virtual void setColor(Color color);

		virtual void setVertPos(int i, float x, float y, float z);
		virtual void setVertTex(int i, float u, float v);
		virtual void setVertColor(int i, Color color);

	private:
    
    GLUSshape mShape;
    GLuint mNumIndices;

	};
};
