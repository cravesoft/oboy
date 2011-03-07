#include "LinuxLineStrip.h"

#include <assert.h>
#include "LinuxGLInterface.h"
#include <iostream>

using namespace OBoy;

LinuxLineStrip::LinuxLineStrip(int numVerts)
{
	mVertices.clear();
  mColors.clear();
	mTexCoords.clear();
  mTangents.clear();
  mNormals.clear();
  mIndices.clear();

  mNumVerts = numVerts;

  mVertices.resize(numVerts);
  mColors.resize(4*numVerts);
  mIndices.resize(numVerts);
  for (int i=0 ; i<mNumVerts ; i++)
    mIndices[i] = i;
}

void LinuxLineStrip::setVertPos(int i, float x, float y, float z)
{
  assert(i < mNumVerts);
	mVertices[i].x() = x;
  mVertices[i].y() = y;
  mVertices[i].z() = z;
}

void LinuxLineStrip::setVertColor(int i, OBoyLib::Color color)
{
  assert(i < mNumVerts);
	mColors[4*i+0] = color.r;
  mColors[4*i+1] = color.g;
  mColors[4*i+2] = color.b;
  mColors[4*i+3] = color.a;
}

void LinuxLineStrip::setColor(OBoyLib::Color color)
{
	for (int i=0 ; i<mNumVerts ; i++)
	{
		mColors[4*i+0] = color.r;
    mColors[4*i+1] = color.g;
    mColors[4*i+2] = color.b;
    mColors[4*i+3] = color.a;
	}
}

void LinuxLineStrip::draw()
{
  LinuxShape::draw(0, GL_LINE_STRIP);
}