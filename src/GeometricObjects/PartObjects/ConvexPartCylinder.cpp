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

#include "ConvexPartCylinder.h"

#include <cmath>
#include <limits>
#include <utility>

#include "../../Utilities/Constants.h"

ConvexPartCylinder::ConvexPartCylinder(const float bottom, const float top, const float r, float phi1, float phi2)
    : GeometricObject(), y0(bottom), y1(top), radius(r), inv_radius(1.0f / r), phi_min(phi1), phi_max(phi2) {}

ConvexPartCylinder::ConvexPartCylinder(const ConvexPartCylinder& c) : GeometricObject(c), y0(c.y0), y1(c.y1), radius(c.radius), inv_radius(c.inv_radius), phi_min(c.phi_min), phi_max(c.phi_max) {}

ConvexPartCylinder::ConvexPartCylinder(ConvexPartCylinder&& c) noexcept
    : GeometricObject(std::move(c)),
      y0(std::exchange(c.y0, -1.0f)),
      y1(std::exchange(c.y1, 1.0f)),
      radius(std::exchange(c.radius, 1.0f)),
      inv_radius(std::exchange(c.inv_radius, 1.0f)),
      phi_min(std::exchange(c.phi_min, 0.0f)),
      phi_max(std::exchange(c.phi_max, 180.0f)) {}

ConvexPartCylinder& ConvexPartCylinder::operator=(const ConvexPartCylinder& c) {
    GeometricObject::operator=(c);

    y0 = c.y0;
    y1 = c.y1;
    radius = c.radius;
    inv_radius = c.inv_radius;
    phi_min = c.phi_min;
    phi_max = c.phi_max;

    return *this;
}

ConvexPartCylinder& ConvexPartCylinder::operator=(ConvexPartCylinder&& c) noexcept {
    GeometricObject::operator=(std::move(c));

    y0 = std::exchange(c.y0, -1.0f);
    y1 = std::exchange(c.y1, 1.0f);
    radius = std::exchange(c.radius, 1.0f);
    inv_radius = std::exchange(c.inv_radius, 1.0f);
    phi_min = std::exchange(c.phi_min, 0.0f);
    phi_max = std::exchange(c.phi_max, 180.0f);

    return *this;
}

ConvexPartCylinder* ConvexPartCylinder::clone() const { return (new ConvexPartCylinder(*this)); }

bool ConvexPartCylinder::hit(const Ray& ray, float& tmin, ShadeRec& sr) const {
    float t;
    float ox = ray.o.x;
    float oy = ray.o.y;
    float oz = ray.o.z;
    float dx = ray.d.x;
    float dy = ray.d.y;
    float dz = ray.d.z;

    float a = dx * dx + dz * dz;
    float b = 2.0 * (ox * dx + oz * dz);
    float c = ox * ox + oz * oz - radius * radius;
    float disc = b * b - 4.0 * a * c;

    if (disc < 0.0f) {
        return false;
    } else {
        float e = sqrt(disc);
        float denom = 2.0 * a;
        t = (-b - e) / denom;  // smaller root

        for (int ii = 0; ii < 2; ii++) {
            if (t > std::numeric_limits<float>::epsilon()) {
                float yhit = oy + t * dy;

                if (yhit > y0 && yhit < y1) {
                    float xhit = ox + t * dx, zhit = oz + t * dz;
                    sr.normal = Normal(xhit * inv_radius, 0.0f, zhit * inv_radius);

                    float phi = atan2(xhit, zhit);
                    if (phi < 0.0f) {
                        phi += TWO_PI;
                    }

                    if (phi >= phi_min * PI_ON_180 && phi <= phi_max * PI_ON_180) {
                        tmin = t;
                        if (-ray.d * sr.normal < 0.0f) {
                            sr.normal = -sr.normal;
                        }

                        sr.local_hit_point = ray.o + tmin * ray.d;

                        return true;
                    }
                }
            }

            t = (-b + e) / denom;  // larger root
        }
    }

    return false;
}

BBox ConvexPartCylinder::get_bounding_box() const {
    Point3D p1(-radius, y0, -radius), p2(radius, y1, radius);
    return BBox(p1, p2);
}
