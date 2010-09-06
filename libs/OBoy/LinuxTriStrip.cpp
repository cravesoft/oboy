#include "LinuxTriStrip.h"

using namespace OBoy;

LinuxTriStrip::LinuxTriStrip(int numVerts)
{
  mShape.numberVertices = numVerts;
  mShape.numberIndices = numVerts;

  mShape.vertices = (GLUSfloat*)malloc(4*numVerts*sizeof(GLUSfloat));
	memset(mShape.vertices, 0, 4*numVerts*sizeof(GLUSfloat));

  mShape.texCoords = (GLUSfloat*)malloc(2*numVerts*sizeof(GLUSfloat));
	memset(mShape.texCoords, 0, 2*numVerts*sizeof(GLUSfloat));

  mNumIndices = mShape.numberIndices;
}

LinuxTriStrip::~LinuxTriStrip()
{
	glusDestroyShapef(&mShape);
}

void LinuxTriStrip::setVertPos(int i, float x, float y, float z)
{
	mShape.vertices[i*4+0] = x;
  mShape.vertices[i*4+1] = y;
  mShape.vertices[i*4+2] = z;
  mShape.vertices[i*4+3] = 1.0f;
}

void LinuxTriStrip::setVertTex(int i, float u, float v)
{
  mShape.texCoords[i*2+0] = u;
  mShape.texCoords[i*2+0] = v;
}

void LinuxTriStrip::setVertColor(int i, Color color)
{
//	mVerts[i].color = (D3DCOLOR)color; // both are ARGB format
}

void LinuxTriStrip::setColor(Color color)
{
/*	for (int i=0 ; i<mVertexCount ; i++)
	{
		mVerts[i].color = (D3DCOLOR)color;
	}*/
}
