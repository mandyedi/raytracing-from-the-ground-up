



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
#include "Torus.h"
#include "../Utilities/Maths.h"

Torus::Torus (void)
    :   GeometricObject(),
    a(2.0),
    b(0.5),
    bbox(-a - b, a + b, -b, b, -a - b, a + b)
{}

Torus::Torus (const double _a, const double _b)
    :   GeometricObject(),
    a(_a),
    b(_b),
    bbox(-a - b, a + b, -b, b, -a - b, a + b)
{}

Torus::Torus (const Torus& t)
    :    GeometricObject(t),
         a(t.a),
         b(t.b),
         bbox(t.bbox)
{

}

Torus::Torus (Torus&& t) noexcept
    :    GeometricObject(std::move(t)),
         a(std::exchange(t.a, 2.0)),
         b(std::exchange(t.b, 0.5)),
         bbox(std::move(t.bbox))
{

}

Torus&
Torus::operator= (const Torus& t) {
    GeometricObject::operator=(t);

    a    = t.a;
    b    = t.b;
    bbox = t.bbox;

    return *this;
}

Torus&
Torus::operator= (Torus&& t) noexcept {
    GeometricObject::operator=(std::move(t));

    a    = std::exchange(t.a, 2.0);
    b    = std::exchange(t.b, 0.5);
    bbox = std::move(t.bbox);

    return *this;
}

Normal
Torus::compute_normal(const Point3D& p) const {
    Normal normal;
    double param_squared = a * a + b * b;

    double x = p.x;
    double y = p.y;
    double z = p.z;
    double sum_squared = x * x + y * y + z * z;

    normal.x = 4.0 * x * (sum_squared - param_squared);
    normal.y = 4.0 * y * (sum_squared - param_squared + 2.0 * a * a);
    normal.z = 4.0 * z * (sum_squared - param_squared);
    normal.normalize();

    return (normal);
}



bool
Torus::hit(const Ray& ray, double& tmin, ShadeRec& sr) const {
    if (!bbox.hit(ray))
    {
        return (false);
    }

    double x1 = ray.o.x; double y1 = ray.o.y; double z1 = ray.o.z;
    double d1 = ray.d.x; double d2 = ray.d.y; double d3 = ray.d.z;

    double coeffs[5];    // coefficient array for the quartic equation
    double roots[4];    // solution array for the quartic equation

    // define the coefficients of the quartic equation

    double sum_d_sqrd     = d1 * d1 + d2 * d2 + d3 * d3;
    double e            = x1 * x1 + y1 * y1 + z1 * z1 - a * a - b * b;
    double f            = x1 * d1 + y1 * d2 + z1 * d3;
    double four_a_sqrd    = 4.0 * a * a;

    coeffs[0] = e * e - four_a_sqrd * (b * b - y1 * y1);     // constant term
    coeffs[1] = 4.0 * f * e + 2.0 * four_a_sqrd * y1 * d2;
    coeffs[2] = 2.0 * sum_d_sqrd * e + 4.0 * f * f + four_a_sqrd * d2 * d2;
    coeffs[3] = 4.0 * sum_d_sqrd * f;
    coeffs[4] = sum_d_sqrd * sum_d_sqrd;                      // coefficient of t^4

    // find roots of the quartic equation

    int num_real_roots = SolveQuartic(coeffs, roots);

    bool    intersected = false;
    double  t           = std::numeric_limits<double>::max();

    if (num_real_roots == 0)  // ray misses the torus
    {
        return (false);
    }

    // find the smallest root greater than epsilon, if any
    // the roots array is not sorted

    for (int j = 0; j < num_real_roots; j++)
        if (roots[j] > std::numeric_limits<double>::epsilon()) {
            intersected = true;
            if (roots[j] < t)
            {
                t = roots[j];
            }
        }

    if(!intersected)
    {
        return (false);
    }

    tmin                  = t;
    sr.local_hit_point     = ray.o + t * ray.d;
    sr.normal              = compute_normal(sr.local_hit_point);

    return (true);
}
