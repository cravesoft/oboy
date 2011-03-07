#pragma once

#include "TriStrip.h"
#include "LinuxShape.h"

namespace OBoy
{
	class LinuxTriStrip : public LinuxShape, public TriStrip
	{
	public:

		LinuxTriStrip(int numVerts);
    virtual ~LinuxTriStrip() {};

		virtual void setColor(OBoyLib::Color color);

		virtual void setVertPos(int i, float x, float y, float z);
		virtual void setVertTex(int i, float u, float v);
		virtual void setVertColor(int i, OBoyLib::Color color);

    virtual bool build() { return LinuxShape::build(); };

    virtual void draw();

  private:

    int mNumVerts;

	};
};
