#pragma once

#include "d3d9.h"
#include "TriStrip.h"
#include "WinD3DInterface.h"

namespace OBoy
{
	class WinTriStrip : public TriStrip
	{
	public:

		WinTriStrip(int numVerts);
		virtual ~WinTriStrip();

    virtual void setColor(OBoyLib::Color color);

		virtual void setVertPos(int i, float x, float y, float z);
		virtual void setVertTex(int i, float u, float v);
    virtual void setVertColor(int i, OBoyLib::Color color);

    virtual bool build();

	public:

		int mVertexCount;
		BoyVertex *mVerts;

	};
};
