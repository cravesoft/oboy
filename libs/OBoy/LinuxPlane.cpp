#include "LinuxPlane.h"

#include <cstring>

using namespace oboy;

LinuxPlane::LinuxPlane(float halfExtend)
{
	unsigned int i, x, y, z;
	unsigned int numVertices = 4;
	unsigned int numIndices = 6;

	float xy_vertices[] =
	{
		-1.0f, -1.0f, 0.0f,
		+1.0f, -1.0f, 0.0f,
		-1.0f, +1.0f, 0.0f,
		+1.0f, +1.0f, 0.0f,
	};

	float xy_normals[] =
	{
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f
	};

	float xy_tangents[] =
	{
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f
	};

	float xy_texCoords[] =
	{
		0.0f, 0.0f,
		1.0f, 0.0f,
		0.0f, 1.0f,
		1.0f, 1.0f
	};

	unsigned int xy_indices[] =
	{
		0, 1, 2,
		1, 3, 2
	};

	mVertices.clear();
  mColors.clear();
	mTexCoords.clear();
  mTangents.clear();
  mNormals.clear();
  mIndices.clear();

  for (i = 0; i < numVertices; i++)
  {
    x = i*3;
    y = x+1;
    z = x+2;
    mVertices.push_back(oboylib::Vector3(xy_vertices[x]*halfExtend, xy_vertices[y]*halfExtend, xy_vertices[z]));
    mNormals.push_back(oboylib::Vector3(xy_normals[x], xy_normals[y], xy_normals[z]));
    mTangents.push_back(oboylib::Vector3(xy_tangents[x], xy_tangents[y], xy_tangents[z]));
    mTexCoords.push_back(oboylib::Vector2(xy_texCoords[i*2], xy_texCoords[i*2+1]));
  }
  mIndices.assign(xy_indices, xy_indices+numIndices);
}

void LinuxPlane::draw()
{
  LinuxShape::draw(0, GL_TRIANGLES);
}