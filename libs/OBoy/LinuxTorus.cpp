#include "LinuxTorus.h"

#include <cstring>
#include "oboylib/OBoyUtil.h"
#include "LinuxImage.h"

using namespace oboy;

LinuxTorus::LinuxTorus(float innerRadius, float outerRadius, unsigned int numSides, unsigned int numFaces)
    : Torus(innerRadius, outerRadius, numSides, numFaces)
{
	// t, s = parametric values of the equations, in the range [0,1]
	float t = 0;
  float s = 0;          
	
	// incr_t, incr_s are increment values aplied to t and s on each loop iteration	to generate the torus
	float tIncr ;
	float sIncr ;

	// to store precomputed sin and cos values 
	float cos2PIt, sin2PIt, cos2PIs, sin2PIs; 

	unsigned int numVertices;
	unsigned int numIndices;

	// used later to help us calculating tangents vectors
  oboylib::Vector3 helpVector(0.0f, 1.0f, 0.0f);

	// indices for each type of buffer (of vertices, indices, normals...)
	unsigned int indexVertices, indexIndices, indexNormals, indexTangents, indexTexCoords;

	// loop counters
	unsigned int sideCount, faceCount;

	// used to generate the indices
	unsigned int v0, v1, v2, v3;

	if (numSides < 3 || numFaces < 3)
	{
		return;
	}	

	numVertices = (numFaces+1) * (numSides+1);
	numIndices  = numFaces * numSides * 2 * 3; // 2 triangles per face * 3 indices per triangle

	mVertices.clear();
  mColors.clear();
	mTexCoords.clear();
  mTangents.clear();
  mNormals.clear();
  mIndices.clear();

  mVertices.resize(numVertices);
  mNormals.resize(numVertices);
  mTangents.resize(numVertices);
  mTexCoords.resize(numVertices);
  mIndices.resize(numIndices);

	tIncr = 1.0f/(float)numFaces;
	sIncr = 1.0f/(float)numSides;

	// generate vertices and its attributes
	for (sideCount = 0; sideCount <= numSides; ++sideCount, s+=sIncr)
	{
		// precompute some values
		cos2PIs = (float)cos (2.0f*OPI*s);  
		sin2PIs = (float)sin (2.0f*OPI*s);

		t=0.0f;
		for (faceCount = 0; faceCount <= numFaces; ++faceCount, t+=tIncr)
		{
			// precompute some values
			cos2PIt = (float)cos (2.0f*OPI*t);
			sin2PIt = (float)sin (2.0f*OPI*t);
			
			// generate vertex and stores it in the right position
			indexVertices = ((sideCount * (numFaces +1)) + faceCount)* 4;
      mVertices[indexVertices].x() = (outerRadius + innerRadius * cos2PIt) * cos2PIs;
      mVertices[indexVertices].y() = (outerRadius + innerRadius * cos2PIt) * sin2PIs;
      mVertices[indexVertices].z() = innerRadius * sin2PIt;

			// generate normal and stores it in the right position
			// NOTE: cos (2PIx) = cos (x) and sin (2PIx) = sin (x) so, we can use this formula
			//       normal = {cos(2PIs)cos(2PIt) , sin(2PIs)cos(2PIt) ,sin(2PIt)}      
			indexNormals = ((sideCount * (numFaces +1)) + faceCount)* 3;
      mNormals[indexNormals].x() = cos2PIs * cos2PIt;
      mNormals[indexNormals].y() = sin2PIs * cos2PIt;
      mNormals[indexNormals].z() = sin2PIt;

			// tangent vector can be calculated with a cross product between the helper vector, and the normal vector
            // We must take care if both the normal and helper are parallel (cross product = 0, that's not a valid tangent!)			
			indexTangents = ((sideCount * (numFaces +1)) + faceCount)* 3;
      mTangents[indexTangents] = mNormals.back().cross(helpVector);

      if (mTangents[indexTangents].magnitudeSquared() == 0.0f)
			{
				mTangents[indexTangents].x() = 1.0f;
				mTangents[indexTangents].y() = 0.0f;
				mTangents[indexTangents].z() = 0.0f;
			}							

			// generate texture coordinates and stores it in the right position
			indexTexCoords = ((sideCount * (numFaces +1)) + faceCount)* 2;
			mTexCoords[indexTexCoords].x() = t;
			mTexCoords[indexTexCoords].y() = s;

		}
	}

	
	// generate indices
  indexIndices = 0;
	for (sideCount = 0; sideCount < numSides; ++sideCount)
	{	
		for (faceCount = 0; faceCount < numFaces; ++faceCount)
		{	
			// get the num of the vertices for a face of the torus. They must be < numVertices
			v0 = ((sideCount * (numFaces +1)) + faceCount);    
			v1 = (((sideCount+1) * (numFaces +1)) + faceCount);
			v2 = (((sideCount+1) * (numFaces +1)) + (faceCount+1));
			v3 = ((sideCount * (numFaces +1)) + (faceCount+1));
			
			// first triangle of the face, counter clock wise winding		
      mIndices.push_back(v0);
			mIndices.push_back(v1);
			mIndices.push_back(v2);

			// second triangle of the face, counter clock wise winding
      mIndices.push_back(v0);
			mIndices.push_back(v2);
			mIndices.push_back(v3);
		}
	}
}

void LinuxTorus::draw()
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