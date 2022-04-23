//  Copyright (C) Kevin Suffern 2000-2007.
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.
//  See the file COPYING.txt for the full license.

//  Copyright notice for changes since the originally published version:
//  Copyright (C) Eduárd Mándy 2019-2021
//  Though this C++ code was change in a large measure it still has the original copyright notice.
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.
//  See the file COPYING.txt for the full license.

#include <utility>
#include <limits>
#include <algorithm>
#include "Triangle.h"



Triangle::Triangle (const Point3D& a, const Point3D& b, const Point3D& c)
    :   GeometricObject(),
        v0(a),
        v1(b),
        v2(c)
{
    compute_normal();
}



Triangle::Triangle (const Triangle& triangle)
    :   GeometricObject(triangle),
        v0(triangle.v0),
        v1(triangle.v1),
        v2(triangle.v2),
        normal(triangle.normal)
{}



Triangle::Triangle (Triangle&& triangle) noexcept
    :   GeometricObject(std::move(triangle)),
        v0(std::move(triangle.v0)),
        v1(std::move(triangle.v1)),
        v2(std::move(triangle.v2)),
        normal(std::move(triangle.normal))
{}



Triangle&
Triangle::operator= (const Triangle& triangle) {
    GeometricObject::operator=(triangle);

    v0      = triangle.v0;
    v1      = triangle.v1;
    v2      = triangle.v2;
    normal  = triangle.normal;

    return (*this);
}



Triangle&
Triangle::operator= (Triangle&& triangle) noexcept {
    GeometricObject::operator=(std::move(triangle));

    v0      = std::move(triangle.v0);
    v1      = std::move(triangle.v1);
    v2      = std::move(triangle.v2);
    normal  = std::move(triangle.normal);

    return (*this);
}



Triangle*
Triangle::clone(void) const {
    return (new Triangle(*this));
}



void
Triangle::compute_normal(void) {
    normal = (v1 - v0) ^ (v2 - v0);
    normal.normalize();
}


BBox
Triangle::get_bounding_box(void) {
    float delta = 0.000001;

    return (BBox(std::min(std::min(v0.x, v1.x), v2.x) - delta, std::max(std::max(v0.x, v1.x), v2.x) + delta,
                 std::min(std::min(v0.y, v1.y), v2.y) - delta, std::max(std::max(v0.y, v1.y), v2.y) + delta,
                 std::min(std::min(v0.z, v1.z), v2.z) - delta, std::max(std::max(v0.z, v1.z), v2.z) + delta));
}



bool
Triangle::hit(const Ray& ray, float& tmin, ShadeRec& sr) const {
    float a = v0.x - v1.x, b = v0.x - v2.x, c = ray.d.x, d = v0.x - ray.o.x;
    float e = v0.y - v1.y, f = v0.y - v2.y, g = ray.d.y, h = v0.y - ray.o.y;
    float i = v0.z - v1.z, j = v0.z - v2.z, k = ray.d.z, l = v0.z - ray.o.z;

    float m = f * k - g * j, n = h * k - g * l, p = f * l - h * j;
    float q = g * i - e * k, s = e * j - f * i;

    float inv_denom  = 1.0f / (a * m + b * q + c * s);

    float e1 = d * m - b * n - c * p;
    float beta = e1 * inv_denom;

    if (beta < 0.0f) {
        return (false);
    }

    float r = r = e * l - h * i;
    float e2 = a * n + d * q + c * r;
    float gamma = e2 * inv_denom;

    if (gamma < 0.0f) {
        return (false);
    }

    if (beta + gamma > 1.0f) {
        return (false);
    }

    float e3 = a * p - b * r + d * s;
    float t = e3 * inv_denom;

    if (t < std::numeric_limits<float>::epsilon()) {
        return (false);
    }

    tmin                = t;
    sr.normal           = normal;
    sr.local_hit_point  = ray.o + t * ray.d;

    return (true);
}



bool
Triangle::shadow_hit(const Ray& ray, float& tmin) const {
    float a = v0.x - v1.x, b = v0.x - v2.x, c = ray.d.x, d = v0.x - ray.o.x;
    float e = v0.y - v1.y, f = v0.y - v2.y, g = ray.d.y, h = v0.y - ray.o.y;
    float i = v0.z - v1.z, j = v0.z - v2.z, k = ray.d.z, l = v0.z - ray.o.z;

    float m = f * k - g * j, n = h * k - g * l, p = f * l - h * j;
    float q = g * i - e * k, s = e * j - f * i;

    float inv_denom  = 1.0f / (a * m + b * q + c * s);

    float e1 = d * m - b * n - c * p;
    float beta = e1 * inv_denom;

    if (beta < 0.0f) {
        return (false);
    }

    float r = e * l - h * i;
    float e2 = a * n + d * q + c * r;
    float gamma = e2 * inv_denom;

    if (gamma < 0.0f) {
        return (false);
    }

    if (beta + gamma > 1.0f) {
        return (false);
    }

    float e3 = a * p - b * r + d * s;
    float t = e3 * inv_denom;

    if (t < std::numeric_limits<float>::epsilon()) {
        return (false);
    }

    tmin = t;

    return(true);
}
