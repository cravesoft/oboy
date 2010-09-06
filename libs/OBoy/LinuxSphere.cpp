#include "LinuxSphere.h"

using namespace OBoy;

LinuxSphere::LinuxSphere(float radius, int numSlices, int numStacks) : Sphere(radius, numSlices, numStacks)
{
	glusCreateSpheref(&mShape, radius, numSlices);
  mNumIndices = mShape.numberIndices;
}

LinuxSphere::~LinuxSphere()
{
  glusDestroyShapef(&mShape);
}

void LinuxSphere::setColor(Color color)
{
}