#include "Circle.h"

#include "OBoyUtil.h"

using namespace oboylib;

#include "CrtDbgNew.h"

Circle::Circle(float x, float y, float radius)
{
	mCenter.x() = x;
	mCenter.y() = y;
	mRadius = radius;
}

Circle::~Circle()
{
}

bool Circle::contains(const Vector2 &point)
{
	return dist(point,mCenter)<=mRadius;
}

Boundary *Circle::clone()
{
	Circle *clone = new Circle(mCenter.x(),mCenter.y(),mRadius);
	return clone;
}

