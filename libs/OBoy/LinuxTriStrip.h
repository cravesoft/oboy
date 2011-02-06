#pragma once

#include "TriStrip.h"
#include "LinuxShape.h"

namespace oboy
{
	class LinuxTriStrip : public LinuxShape, public TriStrip
	{
	public:

		LinuxTriStrip(int numVerts);
    virtual ~LinuxTriStrip() {};

		virtual void setColor(oboylib::Color color);

		virtual void setVertPos(int i, float x, float y, float z);
		virtual void setVertTex(int i, float u, float v);
		virtual void setVertColor(int i, oboylib::Color color);

    virtual bool build() { return LinuxShape::build(); };

    virtual void draw();

  private:

    int mNumVerts;

	};
};
