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
#include "Box.h"
#include "../Utilities/ShadeRec.h"



Box::Box (  const double _x0, const double _x1,
                const double _y0, const double _y1,
                const double _z0, const double _z1)
    : x0(_x0), x1(_x1), y0(_y0), y1(_y1), z0(_z0), z1(_z1)
{}



Box::Box (const Point3D p0, const Point3D p1)
    : x0(p0.x), x1(p1.x), y0(p0.y), y1(p1.y), z0(p0.z), z1(p1.z)
{}



Box::Box (const Box& box)
    : GeometricObject(box), x0(box.x0), x1(box.x1), y0(box.y0), y1(box.y1), z0(box.z0), z1(box.z1)
{}


Box::Box(Box&& box) noexcept
    :   GeometricObject(std::move(box)),
        x0(std::exchange(box.x0, -1.0)),
        x1(std::exchange(box.x1, 1.0)),
        y0(std::exchange(box.y0, -1.0)),
        y1(std::exchange(box.y1, 1.0)),
        z0(std::exchange(box.z0, -1.0)),
        z1(std::exchange(box.z1, 1.0))
{}



Box&
Box::operator= (const Box& box) {
    GeometricObject::operator=(box);
    x0  = box.x0;
    x1  = box.x1;
    y0  = box.y0;
    y1  = box.y1;
    z0  = box.z0;
    z1  = box.z1;

    return (*this);
}


Box &
Box::operator= (Box&& box) noexcept {
    GeometricObject::operator=(std::move(box));
    x0 = std::exchange(box.x0, -1.0);
    x1 = std::exchange(box.x1, 1.0);
    y0 = std::exchange(box.y0, -1.0);
    y1 = std::exchange(box.y1, 1.0);
    z0 = std::exchange(box.z0, -1.0);
    z1 = std::exchange(box.z1, 1.0);

    return (*this);
}



Box*
Box::clone(void) const {
    return (new Box(*this));
}



bool
Box::hit(const Ray& ray, double& tmin, ShadeRec& sr) const {
    // this is the same as Listing 19.1 down to the statement float t0, t1;
    double ox = ray.o.x; double oy = ray.o.y; double oz = ray.o.z;
    double dx = ray.d.x; double dy = ray.d.y; double dz = ray.d.z;

    double tx_min, ty_min, tz_min;
    double tx_max, ty_max, tz_max;

    double a = 1.0 / dx;
    if (a >= 0) {
        tx_min = (x0 - ox) * a;
        tx_max = (x1 - ox) * a;
    }
    else {
        tx_min = (x1 - ox) * a;
        tx_max = (x0 - ox) * a;
    }

    double b = 1.0 / dy;
    if (b >= 0) {
        ty_min = (y0 - oy) * b;
        ty_max = (y1 - oy) * b;
    }
    else {
        ty_min = (y1 - oy) * b;
        ty_max = (y0 - oy) * b;
    }

    double c = 1.0 / dz;
    if (c >= 0) {
        tz_min = (z0 - oz) * c;
        tz_max = (z1 - oz) * c;
    }
    else {
        tz_min = (z1 - oz) * c;
        tz_max = (z0 - oz) * c;
    }

    // ends here (this is the same as Listing 19.1 down to the statement float t0, t1;)

    int face_in, face_out;
    double t0, t1;

    // find largest entering t value

    if (tx_min > ty_min) {
        t0 = tx_min;
        face_in = (a >= 0.0) ? 0 : 3;
    }
    else {
        t0 = ty_min;
        face_in = (b >= 0.0) ? 1 : 4;
    }

    if (tz_min > t0) {
        t0 = tz_min;
        face_in = (c >= 0.0) ? 2 : 5;
    }

    // find smallest exiting t value

    if (tx_max < ty_max) {
        t1 = tx_max;
        face_out = (a >= 0.0) ? 3 : 0;
    }
    else {
        t1 = ty_max;
        face_out = (b >= 0.0) ? 4 : 1;
    }

    if (tz_max < t1) {
        t1 = tz_max;
        face_out = (c >= 0.0) ? 5 : 2;
    }

    if (t0 < t1 && t1 > std::numeric_limits<double>::epsilon()) {  // condition for a hit
        if (t0 > std::numeric_limits<double>::epsilon()) {
            tmin = t0;              // ray hits outside surface
            sr.normal = get_normal(face_in);
        }
        else {
            tmin = t1;              // ray hits inside surface
            sr.normal = get_normal(face_out);
        }

        sr.local_hit_point = ray.o + tmin * ray.d;
        return (true);
    }
    else {
        return (false);
    }
}


// used to test if a ray starts inside a grid
bool
Box::inside(const Point3D& point) const {
    return ((point.x > x0 && point.x < x1) && (point.y > y0 && point.y < y1) && (point.z > z0 && point.z < z1));
};

// todo: refactor, hardcode the Normals into the hit function
Normal
Box::get_normal(const int face_hit) const {
    switch (face_hit) {
        case 0: return (Normal(-1, 0, 0));  // -x face
        case 1: return (Normal(0, -1, 0));  // -y face
        case 2: return (Normal(0, 0, -1));  // -z face
        case 3: return (Normal(1, 0, 0));   // +x face
        case 4: return (Normal(0, 1, 0));   // +y face
        case 5: return (Normal(0, 0, 1));   // +z face
        default: return Normal(1.0, 1.0, 1.0);
    }
}
