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

#include "Vector3D.h"

#include <math.h>

#include "Normal.h"
#include "Point3D.h"

Vector3D::Vector3D(float a) : x(a), y(a), z(a) {}

Vector3D::Vector3D(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}

Vector3D::Vector3D(const Normal& n) : x(n.x), y(n.y), z(n.z) {}

// this is used in the ConcaveHemisphere hit functions

Vector3D::Vector3D(const Point3D& p) : x(p.x), y(p.y), z(p.z) {}

Vector3D& Vector3D::operator=(const Normal& rhs) {
    x = rhs.x;
    y = rhs.y;
    z = rhs.z;
    return *this;
}

Vector3D& Vector3D::operator=(const Point3D& rhs) {
    x = rhs.x;
    y = rhs.y;
    z = rhs.z;
    return *this;
}

float Vector3D::length() { return sqrt(x * x + y * y + z * z); }

void Vector3D::normalize() {
    float length = sqrt(x * x + y * y + z * z);
    x /= length;
    y /= length;
    z /= length;
}

Vector3D& Vector3D::hat() {
    float length = sqrt(x * x + y * y + z * z);
    x /= length;
    y /= length;
    z /= length;
    return *this;
}

Vector3D operator*(const Matrix& mat, const Vector3D& v) {
    return Vector3D(mat.m[0][0] * v.x + mat.m[0][1] * v.y + mat.m[0][2] * v.z, mat.m[1][0] * v.x + mat.m[1][1] * v.y + mat.m[1][2] * v.z, mat.m[2][0] * v.x + mat.m[2][1] * v.y + mat.m[2][2] * v.z);
}
