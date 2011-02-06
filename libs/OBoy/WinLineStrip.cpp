#include "WinLineStrip.h"

#include <assert.h>

using namespace oboy;

#include "oboylib/CrtDbgNew.h"

WinLineStrip::WinLineStrip(int numVerts)
{
	mVertexCount = numVerts;
	mVerts = new BoyVertex[numVerts];
	memset(mVerts, 0, numVerts*sizeof(BoyVertex));
}

WinLineStrip::~WinLineStrip()
{
	delete[] mVerts;
}

void WinLineStrip::setVertPos(int i, float x, float y, float z)
{
	mVerts[i].x = x;
	mVerts[i].y = y;
	mVerts[i].z = z;
}

void WinLineStrip::setVertTex(int i, float u, float v)
{
	mVerts[i].u = u;
	mVerts[i].v = v;
}

void WinLineStrip::setVertColor(int i, oboylib::Color color)
{
	mVerts[i].color = (D3DCOLOR)color.rgba; // both are ARGB format
}

void WinLineStrip::setColor(oboylib::Color color)
{
	for (int i=0 ; i<mVertexCount ; i++)
	{
		mVerts[i].color = (D3DCOLOR)color.rgba;
	}
}

bool WinLineStrip::build()
{
  return 0;
}