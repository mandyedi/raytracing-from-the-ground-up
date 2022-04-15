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
#include <limits>
#include "ConvexPartSphere.h"

ConvexPartSphere::ConvexPartSphere (const Point3D     c,
                                    const double     r,
                                    const double     azimuth_min,    // in degrees
                                    const double     azimuth_max,    // in degrees
                                    const double     polar_min,      // in degrees measured from top
                                    const double     polar_max)      // in degrees measured from top
    :    GeometricObject(),
         center(c),
         radius(r),
         phi_min(azimuth_min * PI_ON_180),            // in radians
         phi_max(azimuth_max * PI_ON_180),            // in radians
         theta_min(polar_min * PI_ON_180),            // in radians measured from top
         theta_max(polar_max * PI_ON_180),            // in radians measured from top
         cos_theta_min(cos(theta_min)),
         cos_theta_max(cos(theta_max))
{}

ConvexPartSphere::ConvexPartSphere (const Point3D c, const double r)
    :    GeometricObject(),
         center(c),
         radius(r),
         phi_min(0.0),
         phi_max(TWO_PI),
         theta_min(0.0),
         theta_max(PI),
         cos_theta_min(1.0),
         cos_theta_max(-1.0)
{}

ConvexPartSphere::ConvexPartSphere (const ConvexPartSphere& c)
    :    GeometricObject(c),
         center(c.center),
         radius(c.radius),
         phi_min(c.phi_min),
         phi_max(c.phi_max),
         theta_min(c.theta_min),
         theta_max(c.theta_max),
         cos_theta_min(c.cos_theta_min),
         cos_theta_max(c.cos_theta_max)
{

}

ConvexPartSphere::ConvexPartSphere (ConvexPartSphere&& c) noexcept
    :    GeometricObject(std::move(c)),
         center(std::move(c.center)),
         radius(std::exchange(c.radius, 1.0)),
         phi_min(std::exchange(c.phi_min, 0.0)),
         phi_max(std::exchange(c.phi_max, TWO_PI)),
         theta_min(std::exchange(c.theta_min, 0.0)),
         theta_max(std::exchange(c.theta_max, PI)),
         cos_theta_min(std::exchange(c.cos_theta_min, 1.0)),
         cos_theta_max(std::exchange(c.cos_theta_max, -1.0))
{

}

ConvexPartSphere&
ConvexPartSphere::operator= (const ConvexPartSphere& c) {
    GeometricObject::operator=(c);

    center        = c.center;
    radius        = c.radius;
    phi_min       = c.phi_min;
    phi_max       = c.phi_max;
    theta_min     = c.theta_min;
    theta_max     = c.theta_max;
    cos_theta_min = c.cos_theta_min;
    cos_theta_max = c.cos_theta_max;

    return *this;
}

ConvexPartSphere&
ConvexPartSphere::operator= (ConvexPartSphere&& c) noexcept {
    GeometricObject::operator=(std::move(c));

    center        = std::move(c.center);
    radius        = std::exchange(c.radius, 1.0);
    phi_min       = std::exchange(c.phi_min, 0.0);
    phi_max       = std::exchange(c.phi_max, TWO_PI);
    theta_min     = std::exchange(c.theta_min, 0.0);
    theta_max     = std::exchange(c.theta_max, PI);
    cos_theta_min = std::exchange(c.cos_theta_min, 1.0);
    cos_theta_max = std::exchange(c.cos_theta_max, -1.0);

    return *this;
}

ConvexPartSphere*
ConvexPartSphere::clone() const {
    return new ConvexPartSphere(*this);
}

bool
ConvexPartSphere::hit(const Ray& ray, double& tmin, ShadeRec& sr) const {
    double          t;
    Vector3D        temp      = ray.o - center;
    double          a         = ray.d * ray.d;
    double          b         = 2.0 * temp * ray.d;
    double          c         = temp * temp - radius * radius;
    double          disc      = b * b - 4.0 * a * c;

    if (disc < 0.0) {
        return(false);
    }
    else {
        double e = sqrt(disc);
        double denom = 2.0 * a;
        t = (-b - e) / denom;    // smaller root

        if (t > std::numeric_limits<double>::epsilon()) {
            Vector3D hit = ray.o + t * ray.d - center;

            double phi = atan2(hit.x, hit.z);
            if (phi < 0.0) {
                phi += TWO_PI;
            }

            if (hit.y <= radius * cos_theta_min &&
                hit.y >= radius * cos_theta_max &&
                phi >= phi_min && phi <= phi_max) {

                tmin = t;
                sr.normal = (temp + t * ray.d) / radius;   // points outwards
                sr.local_hit_point = ray.o + tmin * ray.d;
                return true;
            }
        }

        t = (-b + e) / denom;    // larger root

        if (t > std::numeric_limits<double>::epsilon()) {
            Vector3D hit = ray.o + t * ray.d - center;

            double phi = atan2(hit.x, hit.z);
            if (phi < 0.0) {
                phi += TWO_PI;
            }

            if (hit.y <= radius * cos_theta_min &&
                hit.y >= radius * cos_theta_max &&
                phi >= phi_min && phi <= phi_max) {

                tmin = t;
                sr.normal = (temp + t * ray.d) / radius;   // points outwards
                sr.local_hit_point = ray.o + tmin * ray.d;
                return true;
            }
        }
    }

    return false;
}
