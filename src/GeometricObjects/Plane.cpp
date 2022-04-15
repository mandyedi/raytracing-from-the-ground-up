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
#include "Plane.h"

const double Plane::kEpsilon = 0.001;



Plane::Plane(const Point3D& point, const Normal& normal)
    :   GeometricObject(),
        a(point),
        n(normal)
{
        n.normalize();
}



Plane::~Plane(void)
{}



Plane::Plane(const Plane& p)
    :   GeometricObject(p),
        a(p.a),
        n(p.n)
{}



Plane::Plane(Plane&& p) noexcept
    :   GeometricObject(std::move(p)),
        a(std::move(p.a)),
        n(std::move(p.n))
{}



Plane&
Plane::operator= (const Plane& p)   {
    GeometricObject::operator= (p);

    a = p.a;
    n = p.n;

    return (*this);
}



Plane&
Plane::operator= (Plane&& p) noexcept {
    GeometricObject::operator= (std::move(p));

    a = std::move(p.a);
    n = std::move(p.n);

    return (*this);
}



Plane*
Plane::clone(void) const {
    return (new Plane(*this));
}



bool
Plane::hit(const Ray& ray, double& tmin, ShadeRec& sr) const {
    double t = (a - ray.o) * n / (ray.d * n);

    if (t > kEpsilon) {
        tmin = t;
        sr.normal = n;
        sr.local_hit_point = ray.o + t * ray.d;

        return true;
    }

    return false;
}

bool
Plane::shadow_hit(const Ray& ray, float& tmin) const {
    if (!shadows) {
        return false;
    }

    float t = (a - ray.o) * n / (ray.d * n);

    if (t > kEpsilon) {
        tmin = t;
        return true;
    }

    return false;

}
