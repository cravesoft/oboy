#pragma once

#include "CrtDbgInc.h"

#include <math.h>
#include "OBoyMath.h"
#include "Vector2.h"

namespace oboylib
{
	class Vector3
	{
  public:

      /** Type of Vec class.*/
      typedef float valueType;

      /** Number of vector components. */
      enum { numComponents = 3 };
      
      valueType mValues[3];

      Vector3() { mValues[0]=0.0f; mValues[1]=0.0f; mValues[2]=0.0f;}
      Vector3(valueType x,valueType y,valueType z) { mValues[0]=x; mValues[1]=y; mValues[2]=z; }
      Vector3(const Vector2& v2,valueType zz)
      {
          mValues[0] = v2[0];
          mValues[1] = v2[1];
          mValues[2] = zz;
      }


      inline bool operator == (const Vector3& v) const { return mValues[0]==v.mValues[0] && mValues[1]==v.mValues[1] && mValues[2]==v.mValues[2]; }
      
      inline bool operator != (const Vector3& v) const { return mValues[0]!=v.mValues[0] || mValues[1]!=v.mValues[1] || mValues[2]!=v.mValues[2]; }

      inline bool operator <  (const Vector3& v) const
      {
          if (mValues[0]<v.mValues[0]) return true;
          else if (mValues[0]>v.mValues[0]) return false;
          else if (mValues[1]<v.mValues[1]) return true;
          else if (mValues[1]>v.mValues[1]) return false;
          else return (mValues[2]<v.mValues[2]);
      }

      inline valueType* ptr() { return mValues; }
      inline const valueType* ptr() const { return mValues; }

      inline void set( valueType x, valueType y, valueType z)
      {
          mValues[0]=x; mValues[1]=y; mValues[2]=z;
      }

      inline void set( const Vector3& rhs)
      {
          mValues[0]=rhs.mValues[0]; mValues[1]=rhs.mValues[1]; mValues[2]=rhs.mValues[2];
      }

      inline valueType& operator [] (int i) { return mValues[i]; }
      inline valueType operator [] (int i) const { return mValues[i]; }

      inline valueType& x() { return mValues[0]; }
      inline valueType& y() { return mValues[1]; }
      inline valueType& z() { return mValues[2]; }

      inline valueType x() const { return mValues[0]; }
      inline valueType y() const { return mValues[1]; }
      inline valueType z() const { return mValues[2]; }

      /** Dot product. */
      inline valueType operator * (const Vector3& rhs) const
      {
          return mValues[0]*rhs.mValues[0]+mValues[1]*rhs.mValues[1]+mValues[2]*rhs.mValues[2];
      }

      /** Cross product. */
      inline const Vector3 operator ^ (const Vector3& rhs) const
      {
          return Vector3(mValues[1]*rhs.mValues[2]-mValues[2]*rhs.mValues[1],
                       mValues[2]*rhs.mValues[0]-mValues[0]*rhs.mValues[2] ,
                       mValues[0]*rhs.mValues[1]-mValues[1]*rhs.mValues[0]);
      }
      inline const Vector3 cross(const Vector3 &rhs) const
      {
        return Vector3(mValues[1]*rhs.mValues[2]-mValues[2]*rhs.mValues[1],
                       mValues[2]*rhs.mValues[0]-mValues[0]*rhs.mValues[2] ,
                       mValues[0]*rhs.mValues[1]-mValues[1]*rhs.mValues[0]);
      }

      /** Multiply by scalar. */
      inline const Vector3 operator * (valueType rhs) const
      {
          return Vector3(mValues[0]*rhs, mValues[1]*rhs, mValues[2]*rhs);
      }

      /** Unary multiply by scalar. */
      inline Vector3& operator *= (valueType rhs)
      {
          mValues[0]*=rhs;
          mValues[1]*=rhs;
          mValues[2]*=rhs;
          return *this;
      }

      /** Divide by scalar. */
      inline const Vector3 operator / (valueType rhs) const
      {
          return Vector3(mValues[0]/rhs, mValues[1]/rhs, mValues[2]/rhs);
      }

      /** Unary divide by scalar. */
      inline Vector3& operator /= (valueType rhs)
      {
          mValues[0]/=rhs;
          mValues[1]/=rhs;
          mValues[2]/=rhs;
          return *this;
      }

      /** Binary vector add. */
      inline const Vector3 operator + (const Vector3& rhs) const
      {
          return Vector3(mValues[0]+rhs.mValues[0], mValues[1]+rhs.mValues[1], mValues[2]+rhs.mValues[2]);
      }

      /** Unary vector add. Slightly more efficient because no temporary
        * intermediate object.
      */
      inline Vector3& operator += (const Vector3& rhs)
      {
          mValues[0] += rhs.mValues[0];
          mValues[1] += rhs.mValues[1];
          mValues[2] += rhs.mValues[2];
          return *this;
      }

      /** Binary vector subtract. */
      inline const Vector3 operator - (const Vector3& rhs) const
      {
          return Vector3(mValues[0]-rhs.mValues[0], mValues[1]-rhs.mValues[1], mValues[2]-rhs.mValues[2]);
      }

      /** Unary vector subtract. */
      inline Vector3& operator -= (const Vector3& rhs)
      {
          mValues[0]-=rhs.mValues[0];
          mValues[1]-=rhs.mValues[1];
          mValues[2]-=rhs.mValues[2];
          return *this;
      }

      /** Negation operator. Returns the negative of the Vector3. */
      inline const Vector3 operator - () const
      {
          return Vector3 (-mValues[0], -mValues[1], -mValues[2]);
      }

      /** Length of the vector = sqrt( vec . vec ) */
      inline valueType magnitude() const
      {
          return sqrtf( mValues[0]*mValues[0] + mValues[1]*mValues[1] + mValues[2]*mValues[2] );
      }

      /** Length squared of the vector = vec . vec */
      inline valueType magnitudeSquared() const
      {
          return mValues[0]*mValues[0] + mValues[1]*mValues[1] + mValues[2]*mValues[2];
      }

      /** Normalize the vector so that it has length unity.
        * Returns the previous length of the vector.
      */
      inline valueType normalize()
      {
          valueType norm = Vector3::magnitude();
          if (norm>0.0)
          {
              valueType inv = 1.0f/norm;
              mValues[0] *= inv;
              mValues[1] *= inv;
              mValues[2] *= inv;
          }                
          return( norm );
      }

  };

const Vector3 X_AXIS(1.0,0.0,0.0);
const Vector3 Y_AXIS(0.0,1.0,0.0);
const Vector3 Z_AXIS(0.0,0.0,1.0);

}