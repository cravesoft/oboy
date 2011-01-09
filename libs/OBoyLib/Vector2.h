#pragma once

#include "CrtDbgInc.h"

#include <math.h>
#include "OBoyMath.h"

namespace oboylib
{
	class Vector2
	{
	public:
    /** Type of Vec class.*/
    typedef float valueType;

    /** Number of vector components. */
    enum { numComponents = 2 };
    
    /** Vec member variable. */
    valueType mValues[2];
    

    Vector2() {mValues[0]=0.0; mValues[1]=0.0;}
    Vector2(valueType x,valueType y) { mValues[0]=x; mValues[1]=y; }


    inline bool operator == (const Vector2& v) const { return mValues[0]==v.mValues[0] && mValues[1]==v.mValues[1]; }

    inline bool operator != (const Vector2& v) const { return mValues[0]!=v.mValues[0] || mValues[1]!=v.mValues[1]; }

    inline bool operator <  (const Vector2& v) const
    {
        if (mValues[0]<v.mValues[0]) return true;
        else if (mValues[0]>v.mValues[0]) return false;
        else return (mValues[1]<v.mValues[1]);
    }

    inline valueType * ptr() { return mValues; }
    inline const valueType * ptr() const { return mValues; }

    inline void set( valueType x, valueType y ) { mValues[0]=x; mValues[1]=y; }

    inline valueType & operator [] (int i) { return mValues[i]; }
    inline valueType operator [] (int i) const { return mValues[i]; }

    inline valueType & x() { return mValues[0]; }
    inline valueType & y() { return mValues[1]; }

    inline valueType x() const { return mValues[0]; }
    inline valueType y() const { return mValues[1]; }

    /** Dot product. */
    inline valueType operator * (const Vector2& rhs) const
    {
        return mValues[0]*rhs.mValues[0]+mValues[1]*rhs.mValues[1];
    }
    inline valueType dot(const Vector2& rhs) const
    {
        return mValues[0]*rhs.mValues[0]+mValues[1]*rhs.mValues[1];
    }

    /** Multiply by scalar. */
    inline const Vector2 operator * (valueType rhs) const
    {
        return Vector2(mValues[0]*rhs, mValues[1]*rhs);
    }

    /** Unary multiply by scalar. */
    inline Vector2& operator *= (valueType rhs)
    {
        mValues[0]*=rhs;
        mValues[1]*=rhs;
        return *this;
    }

    /** Divide by scalar. */
    inline const Vector2 operator / (valueType rhs) const
    {
        return Vector2(mValues[0]/rhs, mValues[1]/rhs);
    }

    /** Unary divide by scalar. */
    inline Vector2& operator /= (valueType rhs)
    {
        mValues[0]/=rhs;
        mValues[1]/=rhs;
        return *this;
    }

    /** Binary vector add. */
    inline const Vector2 operator + (const Vector2& rhs) const
    {
        return Vector2(mValues[0]+rhs.mValues[0], mValues[1]+rhs.mValues[1]);
    }

    /** Unary vector add. Slightly more efficient because no temporary
      * intermediate object.
    */
    inline Vector2& operator += (const Vector2& rhs)
    {
        mValues[0] += rhs.mValues[0];
        mValues[1] += rhs.mValues[1];
        return *this;
    }

    /** Binary vector subtract. */
    inline const Vector2 operator - (const Vector2& rhs) const
    {
        return Vector2(mValues[0]-rhs.mValues[0], mValues[1]-rhs.mValues[1]);
    }

    /** Unary vector subtract. */
    inline Vector2& operator -= (const Vector2& rhs)
    {
        mValues[0]-=rhs.mValues[0];
        mValues[1]-=rhs.mValues[1];
        return *this;
    }

    /** Negation operator. Returns the negative of the Vector2. */
    inline const Vector2 operator - () const
    {
        return Vector2 (-mValues[0], -mValues[1]);
    }

    /** Length of the vector = sqrt( vec . vec ) */
    inline valueType magnitude() const
    {
        return boy_sqrtf( mValues[0]*mValues[0] + mValues[1]*mValues[1] );
    }

    /** Length squared of the vector = vec . vec */
    inline valueType magnitudeSquared( void ) const
    {
        return mValues[0]*mValues[0] + mValues[1]*mValues[1];
    }

    /** Normalize the vector so that it has length unity.
    */
    inline Vector2 normalize() const { float aMag = magnitude(); return aMag!=0 ? (*this)/aMag : *this; }

    inline Vector2 perp() const { return Vector2(-mValues[1], mValues[0]); }
	};
}