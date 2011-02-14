#include "WinLines.h"

#include <assert.h>

using namespace oboy;

#include "oboylib/CrtDbgNew.h"

WinLines::WinLines(int numVerts)
{
	mVertexCount = numVerts;
	mVerts = new BoyVertex[numVerts];
	memset(mVerts, 0, numVerts*sizeof(BoyVertex));
}

WinLines::~WinLines()
{
	delete[] mVerts;
}

void WinLines::setVertPos(int i, float x, float y, float z)
{
	mVerts[i].x = x;
	mVerts[i].y = y;
	mVerts[i].z = z;
}

void WinLines::setVertTex(int i, float u, float v)
{
	mVerts[i].u = u;
	mVerts[i].v = v;
}

void WinLines::setVertColor(int i, oboylib::Color color)
{
	mVerts[i].color = (D3DCOLOR)color.argb; // both are ARGB format
}

void WinLines::setColor(oboylib::Color color)
{
	for (int i=0 ; i<mVertexCount ; i++)
	{
		mVerts[i].color = (D3DCOLOR)color.argb;
	}
}

bool WinLines::build()
{
  return 0;
}