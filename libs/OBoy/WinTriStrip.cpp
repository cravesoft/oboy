#include "WinTriStrip.h"

#include <assert.h>

using namespace OBoy;

#include "OBoyLib/CrtDbgNew.h"

WinTriStrip::WinTriStrip(int numVerts)
{
	mVertexCount = numVerts;
	mVerts = new BoyVertex[numVerts];
	memset(mVerts, 0, numVerts*sizeof(BoyVertex));
}

WinTriStrip::~WinTriStrip()
{
	delete[] mVerts;
}

void WinTriStrip::setVertPos(int i, float x, float y, float z)
{
	mVerts[i].x = x;
	mVerts[i].y = y;
	mVerts[i].z = z;
}

void WinTriStrip::setVertTex(int i, float u, float v)
{
	mVerts[i].u = u;
	mVerts[i].v = v;
}

void WinTriStrip::setVertColor(int i, OBoyLib::Color color)
{
	mVerts[i].color = (D3DCOLOR)color.argb; // both are ARGB format
}

void WinTriStrip::setColor(OBoyLib::Color color)
{
	for (int i=0 ; i<mVertexCount ; i++)
	{
		mVerts[i].color = (D3DCOLOR)color.argb;
	}
}

bool WinTriStrip::build()
{
  return 0;
}
