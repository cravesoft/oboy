#pragma once

#include "Lines.h"
#include "LinuxShape.h"

namespace OBoy
{
	class LinuxLines : public Lines, public LinuxShape
	{
	public:

		LinuxLines(int numVerts);
    virtual ~LinuxLines() {};

		virtual void setColor(OBoyLib::Color color);

		virtual void setVertPos(int i, float x, float y, float z);
		virtual void setVertColor(int i, OBoyLib::Color color);

    virtual bool build() { return LinuxShape::build(); };

    virtual void draw();

  private:

    int mNumVerts;

	};
};
