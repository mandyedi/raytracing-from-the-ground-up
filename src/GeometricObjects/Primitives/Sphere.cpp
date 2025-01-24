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

#include "Sphere.h"

#include <cmath>
#include <utility>

#include "../../Utilities/Constants.h"

const float Sphere::kEpsilon = 0.001f;

Sphere::Sphere(const Point3D& c, float r) : GeometricObject(), center(c), radius(r) {}

Sphere::~Sphere() {}

Sphere::Sphere(const Sphere& s) : GeometricObject(s), center(s.center), radius(s.radius) {}

Sphere::Sphere(Sphere&& s) noexcept : GeometricObject(std::move(s)), center(std::move(s.center)), radius(std::exchange(s.radius, 1.0f)) {}

Sphere& Sphere::operator=(const Sphere& s) {
    GeometricObject::operator=(s);

    center = s.center;
    radius = s.radius;

    return *this;
}

Sphere& Sphere::operator=(Sphere&& s) noexcept {
    GeometricObject::operator=(std::move(s));

    center = std::move(s.center);
    radius = std::exchange(s.radius, 1.0f);

    return *this;
}

Sphere* Sphere::clone() const { return new Sphere(*this); }

bool Sphere::hit(const Ray& ray, float& tmin, ShadeRec& sr) const {
    Vector3D temp = ray.o - center;
    float a = ray.d * ray.d;
    float b = 2.0 * temp * ray.d;
    float c = temp * temp - radius * radius;
    float disc = b * b - 4.0 * a * c;

    if (disc < 0.0f) {
        return false;
    } else {
        float t;
        float e = sqrt(disc);
        float denom = 2.0 * a;
        t = (-b - e) / denom;  // smaller root

        if (t > kEpsilon) {
            tmin = t;
            sr.normal = (temp + t * ray.d) / radius;
            sr.local_hit_point = ray.o + t * ray.d;
            return true;
        }

        t = (-b + e) / denom;  // larger root

        if (t > kEpsilon) {
            tmin = t;
            sr.normal = (temp + t * ray.d) / radius;
            sr.local_hit_point = ray.o + t * ray.d;
            return true;
        }
    }

    return false;
}

bool Sphere::shadow_hit(const Ray& ray, float& tmin) const {
    if (!shadows) {
        return false;
    }

    Vector3D temp = ray.o - center;
    float a = ray.d * ray.d;
    float b = 2.0 * temp * ray.d;
    float c = temp * temp - radius * radius;
    float disc = b * b - 4.0 * a * c;

    if (disc < 0.0f) {
        return false;
    } else {
        float t;
        float e = sqrt(disc);
        float denom = 2.0 * a;
        t = (-b - e) / denom;  // smaller root

        if (t > kEpsilon) {
            tmin = t;
            return true;
        }

        t = (-b + e) / denom;  // larger root

        if (t > kEpsilon) {
            tmin = t;
            return true;
        }
    }

    return false;
}
