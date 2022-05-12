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

#include "BBox.h"

#include <limits>
#include <utility>

BBox::BBox(const float _x0, const float _x1, const float _y0, const float _y1, const float _z0, const float _z1) : x0(_x0), x1(_x1), y0(_y0), y1(_y1), z0(_z0), z1(_z1) {}

BBox::BBox(const Point3D p0, const Point3D p1) : x0(p0.x), x1(p1.x), y0(p0.y), y1(p1.y), z0(p0.z), z1(p1.z) {}

BBox::BBox(const BBox& bbox) : x0(bbox.x0), x1(bbox.x1), y0(bbox.y0), y1(bbox.y1), z0(bbox.z0), z1(bbox.z1) {}

BBox::BBox(BBox&& bbox) noexcept
    : x0(std::exchange(bbox.x0, -1.0f)),
      x1(std::exchange(bbox.x1, 1.0f)),
      y0(std::exchange(bbox.y0, -1.0f)),
      y1(std::exchange(bbox.y1, 1.0f)),
      z0(std::exchange(bbox.z0, -1.0f)),
      z1(std::exchange(bbox.z1, 1.0f)) {}

BBox& BBox::operator=(const BBox& bbox) {
    x0 = bbox.x0;
    x1 = bbox.x1;
    y0 = bbox.y0;
    y1 = bbox.y1;
    z0 = bbox.z0;
    z1 = bbox.z1;

    return (*this);
}

BBox& BBox::operator=(BBox&& bbox) noexcept {
    x0 = std::exchange(bbox.x0, -1.0f);
    x1 = std::exchange(bbox.x1, 1.0f);
    y0 = std::exchange(bbox.y0, -1.0f);
    y1 = std::exchange(bbox.y1, 1.0f);
    z0 = std::exchange(bbox.z0, -1.0f);
    z1 = std::exchange(bbox.z1, 1.0f);

    return (*this);
}

bool BBox::hit(const Ray& ray) const {
    float ox = ray.o.x;
    float oy = ray.o.y;
    float oz = ray.o.z;
    float dx = ray.d.x;
    float dy = ray.d.y;
    float dz = ray.d.z;

    float tx_min, ty_min, tz_min;
    float tx_max, ty_max, tz_max;

    float a = 1.0f / dx;
    if (a >= 0) {
        tx_min = (x0 - ox) * a;
        tx_max = (x1 - ox) * a;
    } else {
        tx_min = (x1 - ox) * a;
        tx_max = (x0 - ox) * a;
    }

    float b = 1.0f / dy;
    if (b >= 0) {
        ty_min = (y0 - oy) * b;
        ty_max = (y1 - oy) * b;
    } else {
        ty_min = (y1 - oy) * b;
        ty_max = (y0 - oy) * b;
    }

    float c = 1.0f / dz;
    if (c >= 0) {
        tz_min = (z0 - oz) * c;
        tz_max = (z1 - oz) * c;
    } else {
        tz_min = (z1 - oz) * c;
        tz_max = (z0 - oz) * c;
    }

    float t0, t1;

    // find largest entering t value

    if (tx_min > ty_min)
        t0 = tx_min;
    else
        t0 = ty_min;

    if (tz_min > t0) t0 = tz_min;

    // find smallest exiting t value

    if (tx_max < ty_max)
        t1 = tx_max;
    else
        t1 = ty_max;

    if (tz_max < t1) t1 = tz_max;

    return (t0 < t1 && t1 > std::numeric_limits<float>::epsilon());
}

// used to test if a ray starts inside a grid
bool BBox::inside(const Point3D& p) const { return ((p.x > x0 && p.x < x1) && (p.y > y0 && p.y < y1) && (p.z > z0 && p.z < z1)); };
