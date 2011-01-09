#pragma once

#include "LineStrip.h"
#include "LinuxShape.h"

namespace oboy
{
	class LinuxLineStrip : public LinuxShape, public LineStrip
	{
	public:

		LinuxLineStrip(int numVerts);
    virtual ~LinuxLineStrip() {};

		virtual void setColor(Color color);

		virtual void setVertPos(int i, float x, float y, float z);
		virtual void setVertColor(int i, Color color);

    virtual bool build() { return LinuxShape::build(); };

    virtual void draw();

  private:

    int mNumVerts;

	};
};