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

void LinuxTriStrip::setVertColor(int i, Color color)
{
  assert(i < mNumVerts);
  glColor vcolor = parseColor(color);
	mColors[4*i+0] = vcolor.red;
  mColors[4*i+1] = vcolor.green;
  mColors[4*i+2] = vcolor.blue;
  mColors[4*i+3] = vcolor.alpha;
}

void LinuxTriStrip::setColor(Color color)
{
  glColor vcolor = parseColor(color);
	for (int i=0 ; i<mNumVerts ; i++)
	{
		mColors[4*i+0] = vcolor.red;
    mColors[4*i+1] = vcolor.green;
    mColors[4*i+2] = vcolor.blue;
    mColors[4*i+3] = vcolor.alpha;
	}
}

void LinuxTriStrip::draw()
{
  LinuxShape::draw(0, GL_TRIANGLE_STRIP);
}