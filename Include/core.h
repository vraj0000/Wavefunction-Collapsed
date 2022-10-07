
#include "precision.h"
#include <cmath>

#ifndef Vec3_CORE_H
#define Vec3_CORE_H

namespace Renderer {
class Vector3
{
public:
        /** Holds the value along the x axis. */
    real x;

    /** Holds the value along the y axis. */
    real y;

    /** Holds the value along the z axis. */
    real z;

private:
    /** Padding to ensure 4 word alignment. */
    real pad;

public:
    /** The default constructor creates a zero vector. */
    Vector3() : x(0), y(0), z(0) {}

    /**
     * The explicit constructor creates a vector with the given
     * components.
     */
    Vector3(const real x, const real y, const real z)
        : x(x), y(y), z(z) {}

    void invert()
    {
        x = -x;
        y = -y;
        z = -z;
    }

    /** Gets the magnitude of this vector. */
    real magnitude() const
    {
        return real_sqrt(x*x+y*y+z*z);
    }

    /** Gets the squared magnitude of this vector. */
    real squareMagnitude() const
    {
        return x*x+y*y+z*z;
    }

    /** Multiplies this vector by the given scalar. */
    void operator*=(const real value)
    {
        x *= value;
        y *= value;
        z *= value;
    }

    /** Returns a copy of this vector scaled the given value. */
    Vector3 operator*(const real value) const
    {
        return Vector3(x*value, y*value, z*value);
    }

        void operator+=(const Vector3& v)
    {
        x += v.x;
        y += v.y;
        z += v.z;
    }

    /**
     * Returns the value of the given vector added to this.
     */
    Vector3 operator+(const Vector3& v) const
    {
        return Vector3(x+v.x, y+v.y, z+v.z);
    }

    /** Subtracts the given vector from this. */
    void operator-=(const Vector3& v)
    {
        x -= v.x;
        y -= v.y;
        z -= v.z;
    }

    /**
     * Returns the value of the given vector subtracted from this.
     */
    Vector3 operator-(const Vector3& v) const
    {
        return Vector3(x-v.x, y-v.y, z-v.z);
    }
    Vector3 operator/=(const real t) 
    {
        return Vector3(x/t, y/t, z/t);
    }
    
    /**
     * Adds the given vector to this, scaled by the given amount.
     */
    void addScaledVector(const Vector3& vector, real scale)
    {
        x += vector.x * scale;
        y += vector.y * scale;
        z += vector.z * scale;
    }

    /**
     * Calculates and returns a component-wise product of this
     * vector with the given vector.
     */
    Vector3 componentProduct(const Vector3 &vector) const
    {
        return Vector3(x * vector.x, y * vector.y, z * vector.z);
    }

    /**
     * Performs a component-wise product with the given vector and
     * sets this vector to its result.
     */
    void componentProductUpdate(const Vector3 &vector)
    {
        x *= vector.x;
        y *= vector.y;
        z *= vector.z;
    }

    /**
     * Calculates and returns the scalar product of this vector
     * with the given vector.
     */
    real scalarProduct(const Vector3 &vector) const
    {
        return x*vector.x + y*vector.y + z*vector.z;
    }

    /**
     * Calculates and returns the scalar product of this vector
     * with the given vector.
     */
    real operator *(const Vector3 &vector) const
    {
        return x*vector.x + y*vector.y + z*vector.z;
    }

    /**
     * Calculates and returns the vector product of this vector
     * with the given vector.
     */
    Vector3 vectorProduct(const Vector3 &vector) const
    {
        return Vector3(y*vector.z-z*vector.y,
                        z*vector.x-x*vector.z,
                        x*vector.y-y*vector.x);
    }

    /**
     * Updates this vector to be the vector product of its current
     * value and the given vector.
     */
    void operator %=(const Vector3 &vector)
    {
        *this = vectorProduct(vector);
    }

    /**
     * Calculates and returns the vector product of this vector
     * with the given vector.
     */
    Vector3 operator%(const Vector3 &vector) const
    {
        return Vector3(y*vector.z-z*vector.y,
                        z*vector.x-x*vector.z,
                        x*vector.y-y*vector.x);
    }

    /**
     * clears the value of x,y and z. 
     */
    Vector3 clear()
    {
        x = y = z = 0;
    }

    
};

// Type aliases for vec3
using point3 = Vector3;   // 3D point
using color = Vector3;    // RGB color
}
#endif // CYCLONE_CORE_H