#pragma once

#include "LineStrip.h"
#include "LinuxShape.h"

namespace OBoy
{
	class LinuxLineStrip : public LinuxShape, public LineStrip
	{
	public:

		LinuxLineStrip(int numVerts);
    virtual ~LinuxLineStrip() {};

		virtual void setColor(OBoyLib::Color color);

		virtual void setVertPos(int i, float x, float y, float z);
		virtual void setVertColor(int i, OBoyLib::Color color);

    virtual bool build() { return LinuxShape::build(); };

    virtual void draw();

  private:

    int mNumVerts;

	};
};