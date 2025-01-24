//  Copyright (C) Kevin Suffern 2000-2007.
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.
//  See the file COPYING.txt for the full license.

//  Copyright notice for changes since the originally published version:
//  Copyright (C) Eduárd Mándy 2019-2025
//  Though this C++ code was change in a large measure it still has the original copyright notice.
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.
//  See the file COPYING.txt for the full license.

#ifndef __NORMAL__
#define __NORMAL__

#include "Matrix.h"
#include "Point3D.h"
#include "Vector3D.h"

class Normal {
public:

    float x = 0.0f;
    float y = 0.0f;
    float z = 0.0f;

public:

    Normal() = default;
    explicit Normal(float a);
    explicit Normal(float _x, float _y, float _z);
    explicit Normal(const Vector3D& v);

    Normal& operator=(const Vector3D& rhs);

    Normal& operator=(const Point3D& rhs);

    Normal operator-() const;

    Normal operator+(const Normal& n) const;

    Normal& operator+=(const Normal& n);

    float operator*(const Vector3D& v) const;

    Normal operator*(const float a) const;

    void normalize();
};

inline Normal Normal::operator-() const { return Normal(-x, -y, -z); }

inline Normal Normal::operator+(const Normal& n) const { return Normal(x + n.x, y + n.y, z + n.z); }

inline Normal& Normal::operator+=(const Normal& n) {
    x += n.x;
    y += n.y;
    z += n.z;
    return *this;
}

inline float Normal::operator*(const Vector3D& v) const { return x * v.x + y * v.y + z * v.z; }

inline Normal Normal::operator*(const float a) const { return Normal(x * a, y * a, z * a); }

Normal operator*(const float a, const Normal& n);

inline Normal operator*(const float f, const Normal& n) { return Normal(f * n.x, f * n.y, f * n.z); }

Vector3D operator+(const Vector3D& v, const Normal& n);

inline Vector3D operator+(const Vector3D& v, const Normal& n) { return Vector3D(v.x + n.x, v.y + n.y, v.z + n.z); }

Vector3D operator-(const Vector3D&, const Normal& n);

inline Vector3D operator-(const Vector3D& v, const Normal& n) { return Vector3D(v.x - n.x, v.y - n.y, v.z - n.z); }

float operator*(const Vector3D& v, const Normal& n);

inline float operator*(const Vector3D& v, const Normal& n) { return v.x * n.x + v.y * n.y + v.z * n.z; }

Normal operator*(const Matrix& mat, const Normal& n);

#endif
