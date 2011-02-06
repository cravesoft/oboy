#pragma once

#include "oboylib/CrtDbgInc.h"
#include "Graphics.h"

namespace oboy
{
	class TriStrip
	{
	public:

		TriStrip() {}
		virtual ~TriStrip() {}

    virtual void setColor(oboylib::Color color) = 0;

		virtual void setVertPos(int i, float x, float y, float z=0) = 0;
		virtual void setVertTex(int i, float u, float v) = 0;
    virtual void setVertColor(int i, oboylib::Color color) = 0;

    virtual bool build() = 0;
	};
}
