#pragma once

#include "d3d9.h"
#include "TriStrip.h"
#include "WinD3DInterface.h"

namespace oboy
{
	class WinTriStrip : public TriStrip
	{
	public:

		WinTriStrip(int numVerts);
		virtual ~WinTriStrip();

    virtual void setColor(oboylib::Color color);

		virtual void setVertPos(int i, float x, float y, float z);
		virtual void setVertTex(int i, float u, float v);
    virtual void setVertColor(int i, oboylib::Color color);

    virtual bool build();

	public:

		int mVertexCount;
		BoyVertex *mVerts;

	};
};
