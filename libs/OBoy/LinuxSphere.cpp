#include "LinuxSphere.h"

#include "LinuxGLInterface.h"
#include "oboylib/OBoyUtil.h"
#include "LinuxImage.h"

using namespace oboy;

LinuxSphere::LinuxSphere(float radius, unsigned int numSlices, unsigned int numStacks) : Sphere(radius, numSlices, numStacks)
{
  unsigned int i,j;

	unsigned int numParallels = numSlices;
	unsigned int numVertices = ( numParallels + 1 ) * ( numSlices + 1 );
	unsigned int numIndices = numParallels * numSlices * 6;

	float angleStep = (2.0f * OPI) / ((float) numSlices);

	unsigned int* indexBuf;

  oboylib::Vector3 helpVector(0.0f, 1.0f, 0.0f);

	mVertices.clear();
  mColors.clear();
	mTexCoords.clear();
  mTangents.clear();
  mNormals.clear();
  mIndices.clear();

	for (i = 0; i < numParallels + 1; i++)
	{
    for (j = 0; j < numSlices + 1; j++)
		{
      oboylib::Vector3 vertex(
        radius * sinf(angleStep * (float)i) * sinf(angleStep * (float)j),
        radius * cosf(angleStep * (float)i),
        radius * sinf(angleStep * (float)i) * cosf(angleStep * (float)j));
      mVertices.push_back(vertex);

      mColors.push_back(1.0f); /* red */
      mColors.push_back(1.0f); /* green */
      mColors.push_back(1.0f); /* blue */
      mColors.push_back(1.0f); /* alpha */

      mNormals.push_back(oboylib::Vector3(
        vertex.x() / radius,
        vertex.y() / radius,
        vertex.z() / radius));

      oboylib::Vector3 tangent;
      tangent = mNormals.back().cross(helpVector);
      if (tangent.magnitudeSquared() == 0.0f)
			{
				tangent.x() = 1.0f;
        tangent.y() = 0.0f;
        tangent.z() = 0.0f;
			}
      mTangents.push_back(tangent);

      mTexCoords.push_back(oboylib::Vector2(
        (float) j / (float) numSlices,
        ( 1.0f - (float) i ) / (float) (numParallels - 1 )));
		}
	}

  mIndices.resize(numIndices);
	indexBuf = &mIndices[0];
	for (i = 0; i < numParallels; i++)
	{
		for (j = 0; j < numSlices; j++)
		{
			*indexBuf++  = i * ( numSlices + 1 ) + j;
			*indexBuf++ = ( i + 1 ) * ( numSlices + 1 ) + j;
			*indexBuf++ = ( i + 1 ) * ( numSlices + 1 ) + ( j + 1 );

			*indexBuf++ = i * ( numSlices + 1 ) + j;
			*indexBuf++ = ( i + 1 ) * ( numSlices + 1 ) + ( j + 1 );
			*indexBuf++ = i * ( numSlices + 1 ) + ( j + 1 );
		}
	}
}

void LinuxSphere::setColor(Color color)
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

void LinuxSphere::draw()
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