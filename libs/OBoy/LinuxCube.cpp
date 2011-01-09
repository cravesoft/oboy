#include "LinuxCube.h"

#include <cstring>
#include "OBoyLib/Vector3.h"
#include "LinuxGLInterface.h"
#include "LinuxImage.h"

using namespace oboy;

LinuxCube::LinuxCube(float halfExtend) : Cube(halfExtend)
{
	unsigned int i, x, y, z;

	unsigned int numVertices = 24;
	unsigned int numIndices = 36;

  float cubeVertices[] =
	{
	  -1.0f, -1.0f, -1.0f,
	  -1.0f, -1.0f, +1.0f,
	  +1.0f, -1.0f, +1.0f,
	  +1.0f, -1.0f, -1.0f,
	  -1.0f, +1.0f, -1.0f,
	  -1.0f, +1.0f, +1.0f,
	  +1.0f, +1.0f, +1.0f,
	  +1.0f, +1.0f, -1.0f,
	  -1.0f, -1.0f, -1.0f,
	  -1.0f, +1.0f, -1.0f,
	  +1.0f, +1.0f, -1.0f,
	  +1.0f, -1.0f, -1.0f,
	  -1.0f, -1.0f, +1.0f,
	  -1.0f, +1.0f, +1.0f,
	  +1.0f, +1.0f, +1.0f,
	  +1.0f, -1.0f, +1.0f,
	  -1.0f, -1.0f, -1.0f,
	  -1.0f, -1.0f, +1.0f,
	  -1.0f, +1.0f, +1.0f,
	  -1.0f, +1.0f, -1.0f,
	  +1.0f, -1.0f, -1.0f,
	  +1.0f, -1.0f, +1.0f,
	  +1.0f, +1.0f, +1.0f,
	  +1.0f, +1.0f, -1.0f,
	};

	float cubeNormals[] =
	{
	   0.0f, -1.0f,  0.0f,
	   0.0f, -1.0f,  0.0f,
	   0.0f, -1.0f,  0.0f,
	   0.0f, -1.0f,  0.0f,
	   0.0f, +1.0f,  0.0f,
	   0.0f, +1.0f,  0.0f,
	   0.0f, +1.0f,  0.0f,
	   0.0f, +1.0f,  0.0f,
	   0.0f,  0.0f, -1.0f,
	   0.0f,  0.0f, -1.0f,
	   0.0f,  0.0f, -1.0f,
	   0.0f,  0.0f, -1.0f,
	   0.0f,  0.0f, +1.0f,
	   0.0f,  0.0f, +1.0f,
	   0.0f,  0.0f, +1.0f,
	   0.0f,  0.0f, +1.0f,
	  -1.0f,  0.0f,  0.0f,
	  -1.0f,  0.0f,  0.0f,
	  -1.0f,  0.0f,  0.0f,
	  -1.0f,  0.0f,  0.0f,
	  +1.0f,  0.0f,  0.0f,
	  +1.0f,  0.0f,  0.0f,
	  +1.0f,  0.0f,  0.0f,
	  +1.0f,  0.0f,  0.0f
	};

	float cubeTangents[] =
	{
	  -1.0f,  0.0f,  0.0f,
	  -1.0f,  0.0f,  0.0f,
	  -1.0f,  0.0f,  0.0f,
	  -1.0f,  0.0f,  0.0f,

	  +1.0f,  0.0f,  0.0f,
	  +1.0f,  0.0f,  0.0f,
	  +1.0f,  0.0f,  0.0f,
	  +1.0f,  0.0f,  0.0f,

	  -1.0f,  0.0f,  0.0f,
	  -1.0f,  0.0f,  0.0f,
	  -1.0f,  0.0f,  0.0f,
	  -1.0f,  0.0f,  0.0f,

	  +1.0f,  0.0f,  0.0f,
	  +1.0f,  0.0f,  0.0f,
	  +1.0f,  0.0f,  0.0f,
	  +1.0f,  0.0f,  0.0f,

	   0.0f,  0.0f, +1.0f,
	   0.0f,  0.0f, +1.0f,
	   0.0f,  0.0f, +1.0f,
	   0.0f,  0.0f, +1.0f,

	   0.0f,  0.0f, -1.0f,
	   0.0f,  0.0f, -1.0f,
	   0.0f,  0.0f, -1.0f,
	   0.0f,  0.0f, -1.0f
	};

	float cubeTexCoords[] =
	{
	  0.0f, 0.0f,
	  0.0f, 1.0f,
	  1.0f, 1.0f,
	  1.0f, 0.0f,
	  1.0f, 0.0f,
	  1.0f, 1.0f,
	  0.0f, 1.0f,
	  0.0f, 0.0f,
	  0.0f, 0.0f,
	  0.0f, 1.0f,
	  1.0f, 1.0f,
	  1.0f, 0.0f,
	  0.0f, 0.0f,
	  0.0f, 1.0f,
	  1.0f, 1.0f,
	  1.0f, 0.0f,
	  0.0f, 0.0f,
	  0.0f, 1.0f,
	  1.0f, 1.0f,
	  1.0f, 0.0f,
	  0.0f, 0.0f,
	  0.0f, 1.0f,
	  1.0f, 1.0f,
	  1.0f, 0.0f,
	};
   
	unsigned int cubeIndices[] =
	{
	 0, 2, 1,
	 0, 3, 2, 
	 4, 5, 6,
	 4, 6, 7,
	 8, 9, 10,
	 8, 10, 11, 
	 12, 15, 14,
	 12, 14, 13, 
	 16, 17, 18,
	 16, 18, 19, 
	 20, 23, 22,
	 20, 22, 21
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
    mVertices.push_back(oboylib::Vector3(cubeVertices[x]*halfExtend,
      cubeVertices[y]*halfExtend,
      cubeVertices[z]*halfExtend));
    mNormals.push_back(oboylib::Vector3(cubeNormals[x], cubeNormals[y], cubeNormals[z]));
    mTangents.push_back(oboylib::Vector3(cubeTangents[x], cubeTangents[y], cubeTangents[z]));
    mTexCoords.push_back(oboylib::Vector2(cubeTexCoords[i*2], cubeTexCoords[i*2+1]));
  }
  mIndices.assign(cubeIndices, cubeIndices+numIndices);
}

void LinuxCube::setColor(Color color)
{
  glColor vcolor = parseColor(color);
  for (int i=0 ; i<(int)mColors.size() ; i+=4)
  {
    mColors[i+0] = vcolor.red;
    mColors[i+1] = vcolor.green;
    mColors[i+2] = vcolor.blue;
    mColors[i+3] = vcolor.alpha;
  }
}

void LinuxCube::draw()
{
  oboy::Image *img = this->getTexture();

  if (img == NULL)
  {
  	// draw the sphere without texture:
    LinuxShape::draw(0, GL_TRIANGLES);
    return;
  }

  LinuxImage *image = dynamic_cast<LinuxImage*>(img);

  LinuxShape::draw(image->getTexture(), GL_TRIANGLES);
}