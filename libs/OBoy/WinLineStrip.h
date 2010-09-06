#pragma once

#include "d3d9.h"
#include "LineStrip.h"
#include "WinD3DInterface.h"

namespace OBoy
{
	class WinLineStrip : public LineStrip
	{
	public:

		WinLineStrip(int numVerts);
		virtual ~WinLineStrip();

		virtual void setColor(Color color);

		virtual void setVertPos(int i, float x, float y, float z);
		virtual void setVertTex(int i, float u, float v);
		virtual void setVertColor(int i, Color color);

	public:

		int mVertexCount;
		BoyVertex *mVerts;

	};
};
