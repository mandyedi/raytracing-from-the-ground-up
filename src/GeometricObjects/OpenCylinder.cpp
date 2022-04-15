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
#include "OpenCylinder.h"

const double OpenCylinder::kEpsilon = 0.001;



OpenCylinder::OpenCylinder(double bottom, double top, double radius)
    : GeometricObject(),
      y0(bottom),
      y1(top),
      radius(radius),
      inv_radius(1.0 / radius)
{}



OpenCylinder::OpenCylinder (const OpenCylinder& oc)
  : GeometricObject(oc),
    y0(oc.y0),
    y1(oc.y1),
    radius(oc.radius),
    inv_radius(oc.inv_radius)
{}



OpenCylinder::OpenCylinder (OpenCylinder&& oc) noexcept
  : GeometricObject(std::move(oc)),
    y0(std::exchange(oc.y0, 0.0)),
    y1(std::exchange(oc.y1, 0.0)),
    radius(std::exchange(oc.radius, 1.0)),
    inv_radius(std::exchange(oc.inv_radius, 1.0))
{}



OpenCylinder&
OpenCylinder::operator= (const OpenCylinder& oc) {
  GeometricObject::operator=(oc);

  y0 = oc.y0, 0.0;
  y1 = oc.y1, 0.0;
  radius = oc.radius, 1.0;
  inv_radius = oc.inv_radius, 1.0;

  return (*this);
}



OpenCylinder&
OpenCylinder::operator= (OpenCylinder&& oc) noexcept {
  GeometricObject::operator=(std::move(oc));

  y0 = std::exchange(oc.y0, 0.0);
  y1 = std::exchange(oc.y1, 0.0);
  radius = std::exchange(oc.radius, 1.0);
  inv_radius = std::exchange(oc.inv_radius, 1.0);

  return (*this);
}



OpenCylinder*
OpenCylinder::clone(void) const {
  return (new OpenCylinder(*this));
}



bool
OpenCylinder::hit(const Ray& ray, double& tmin, ShadeRec& sr) const {
  double t;
  double ox = ray.o.x;
  double oy = ray.o.y;
  double oz = ray.o.z;
  double dx = ray.d.x;
  double dy = ray.d.y;
  double dz = ray.d.z;

  double a = dx * dx + dz * dz;
  double b = 2.0 * (ox * dx + oz * dz);
  double c = ox * ox + oz * oz - radius * radius;
  double disc = b * b - 4.0 * a * c ;


  if (disc < 0.0) {
    return(false);
  }
  else {
    double e = sqrt(disc);
    double denom = 2.0 * a;
    t = (-b - e) / denom;    // smaller root

    if (t > kEpsilon) {
      double yhit = oy + t * dy;

      if (yhit > y0 && yhit < y1) {
        tmin = t;
        sr.normal = Normal((ox + t * dx) * inv_radius, 0.0, (oz + t * dz) * inv_radius);

        // test for hitting from inside

        if (-ray.d * sr.normal < 0.0) {
          sr.normal = -sr.normal;
        }

        sr.local_hit_point = ray.o + tmin * ray.d;

        return (true);
      }
    }

    t = (-b + e) / denom;    // larger root

    if (t > kEpsilon) {
      double yhit = oy + t * dy;

      if (yhit > y0 && yhit < y1) {
        tmin = t;
        sr.normal = Normal((ox + t * dx) * inv_radius, 0.0, (oz + t * dz) * inv_radius);

        // test for hitting inside surface

        if (-ray.d * sr.normal < 0.0) {
          sr.normal = -sr.normal;
        }

        sr.local_hit_point = ray.o + tmin * ray.d;

        return (true);
      }
    }
  }

  return (false);
}
