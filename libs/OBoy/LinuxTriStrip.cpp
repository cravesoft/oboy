#include "LinuxTriStrip.h"

#include <assert.h>
#include "LinuxGLInterface.h"

using namespace oboy;

LinuxTriStrip::LinuxTriStrip(int numVerts)
{
	mVertices.clear();
  mColors.clear();
	mTexCoords.clear();
  mTangents.clear();
  mNormals.clear();
  mIndices.clear();

  mNumVerts = numVerts;

  mVertices.resize(numVerts);
  mTexCoords.resize(numVerts);
  mColors.resize(4*numVerts);
  mIndices.resize(numVerts);
  for (int i=0 ; i<mNumVerts ; i++)
    mIndices[i] = i;
}

void LinuxTriStrip::setVertPos(int i, float x, float y, float z)
{
  assert(i < mNumVerts);
	mVertices[i].x() = x;
  mVertices[i].y() = y;
  mVertices[i].z() = z;
}

void LinuxTriStrip::setVertTex(int i, float u, float v)
{
  assert(i < mNumVerts);
  mTexCoords[i].x() = u;
  mTexCoords[i].y() = v;
}

void LinuxTriStrip::setVertColor(int i, oboylib::Color color)
{
  assert(i < mNumVerts);
	mColors[4*i+0] = color.r;
  mColors[4*i+1] = color.g;
  mColors[4*i+2] = color.b;
  mColors[4*i+3] = color.a;
}

void LinuxTriStrip::setColor(oboylib::Color color)
{
	for (int i=0 ; i<mNumVerts ; i++)
	{
		mColors[4*i+0] = color.r;
    mColors[4*i+1] = color.g;
    mColors[4*i+2] = color.b;
    mColors[4*i+3] = color.a;
	}
}

void LinuxTriStrip::draw()
{
  LinuxShape::draw(0, GL_TRIANGLE_STRIP);
}