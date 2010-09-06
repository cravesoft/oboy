#pragma once

#include "CrtDbgInc.h"

#include <math.h>
#include "OBoyMath.h"

namespace OBoyLib
{
	class Vector3
	{
	public:
		
		Vector3(float x=0, float y=0, float z=0) { this->x = x; this->y = y; this->z = z; }
		Vector3(const Vector3 &vec) { x=vec.x; y=vec.y; z=vec.z; }
		virtual ~Vector3() {}

		Vector3 operator+(const Vector3 &v) const { return Vector3(x+v.x, y+v.y, z+v.z); }
		Vector3 operator-(const Vector3 &v) const { return Vector3(x-v.x, y-v.y, z-v.z); }
		Vector3 operator-() const { return Vector3(-x, -y, -z); }
		Vector3 operator*(float t) const { return Vector3(t*x, t*y, t*z); }
		Vector3 operator/(float t) const { return Vector3(x/t, y/t, z/t); }
		void operator+=(const Vector3 &v) { x+=v.x; y+=v.y; z+=v.z; }
		void operator-=(const Vector3 &v) { x-=v.x; y-=v.y; z-=v.z; }
		void operator*=(float t) { x*=t; y*=t; z*=t; }
		void operator/=(float t) { x/=t; y/=t; z/=t; }

		void operator=(const Vector3 &v) { x=v.x; y=v.y; z=v.z; }

		bool operator==(const Vector3 &v) { return x==v.x && y==v.y && z==v.z; }
		bool operator!=(const Vector3 &v) { return x!=v.x || y!=v.y || z!=v.z; }

		float dot(const Vector3 &v) const { return x*v.x + y*v.y + z*v.z; }
		float magnitude() const { return boy_sqrtf(x*x + y*y + z*z); }
		float magnitudeSquared() const { return x*x+y*y+z*z; }

		Vector3 normalize() const { float aMag = magnitude(); return aMag!=0 ? (*this)/aMag : *this; }

		Vector3 perp() const { return Vector3(-y, x, z); }

	public:

		float x;
		float y;
    float z;
	};
}