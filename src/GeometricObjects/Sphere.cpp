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
#include <cmath>
#include "Sphere.h"
#include "../Utilities/Constants.h"

const double Sphere::kEpsilon = 0.001;



Sphere::Sphere(const Point3D& c, double r)
    :   GeometricObject(),
        center(c),
        radius(r)
{}




Sphere::~Sphere(void) {}



Sphere::Sphere(const Sphere& s)
    :   GeometricObject(s),
        center(s.center),
        radius(s.radius)
{}



Sphere::Sphere(Sphere&& s) noexcept
    :   GeometricObject(std::move(s)),
        center(std::move(s.center)),
        radius(std::exchange(s.radius, 1.0))
{}

Sphere&
Sphere::operator= (const Sphere& s) {
    GeometricObject::operator= (s);

    center  = s.center;
    radius  = s.radius;

    return (*this);
}



Sphere&
Sphere::operator= (Sphere&& s) noexcept {
    GeometricObject::operator= (std::move(s));

    center  = std::move(s.center);
    radius  = std::exchange(s.radius, 1.0);

    return (*this);
}




Sphere*
Sphere::clone(void) const {
    return (new Sphere(*this));
}



bool
Sphere::hit(const Ray& ray, double& tmin, ShadeRec& sr) const {
    Vector3D    temp    = ray.o - center;
    double      a       = ray.d * ray.d;
    double      b       = 2.0 * temp * ray.d;
    double      c       = temp * temp - radius * radius;
    double      disc    = b * b - 4.0 * a * c;

    if (disc < 0.0) {
        return(false);
    }
    else {
        double t;
        double e = sqrt(disc);
        double denom = 2.0 * a;
        t = (-b - e) / denom;    // smaller root

        if (t > kEpsilon) {
            tmin = t;
            sr.normal    = (temp + t * ray.d) / radius;
            sr.local_hit_point = ray.o + t * ray.d;
            return (true);
        }

        t = (-b + e) / denom;    // larger root

        if (t > kEpsilon) {
            tmin = t;
            sr.normal   = (temp + t * ray.d) / radius;
            sr.local_hit_point = ray.o + t * ray.d;
            return (true);
        }
    }

    return (false);
}

bool
Sphere::shadow_hit(const Ray& ray, float& tmin) const {
    if (!shadows) {
        return false;
    }

    Vector3D    temp    = ray.o - center;
    double      a       = ray.d * ray.d;
    double      b       = 2.0 * temp * ray.d;
    double      c       = temp * temp - radius * radius;
    double      disc    = b * b - 4.0 * a * c;

    if (disc < 0.0){
        return(false);
    }
    else {
        double t;
        double e = sqrt(disc);
        double denom = 2.0 * a;
        t = (-b - e) / denom;    // smaller root

        if (t > kEpsilon) {
            tmin = t;
            return (true);
        }

        t = (-b + e) / denom;    // larger root

        if (t > kEpsilon) {
            tmin = t;
            return (true);
        }
    }

    return (false);
}





