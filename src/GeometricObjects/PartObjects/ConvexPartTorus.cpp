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
#include <cmath>
#include "ConvexPartTorus.h"
#include "../../Utilities/Constants.h"
#include "../../Utilities/Maths.h"

ConvexPartTorus::ConvexPartTorus()
    :     GeometricObject(),
        a(2.0f),
        b(0.5f),
        phi1(90.0f * PI / 180.0f),
        phi2(270.0f * PI / 180.0f),
        theta1(90.0f * PI / 180.0f),
        theta2(270.0f * PI / 180.0f),
        bbox(-a - b, a + b, -b, b, -a - b, a + b)
{}

// ---------------------------------------------------------------- constructor

ConvexPartTorus::ConvexPartTorus(const float _a,      const float _b,
                                 const float _phi1,   const float _phi2,
                                 const float _theta1, const float _theta2)
    :     GeometricObject(),
        a(_a),
        b(_b),
        phi1(_phi1 * PI / 180.0f),
        phi2(_phi2 * PI / 180.0f),
        theta1(_theta1 * PI / 180.0f),
        theta2(_theta2 * PI / 180.0f),
        bbox(-a - b, a + b, -b, b, -a - b, a + b)
{}

ConvexPartTorus::ConvexPartTorus (const ConvexPartTorus& c)
    :    GeometricObject(c),
         a(c.a),
         b(c.b),
         phi1(c.phi1),
         phi2(c.phi2),
         theta1(c.theta1),
         theta2(c.theta2),
         bbox(c.bbox)
{

}

ConvexPartTorus::ConvexPartTorus (ConvexPartTorus&& c) noexcept
    :    GeometricObject(std::move(c)),
         a(std::exchange(c.a, 2.0f)),
         b(std::exchange(c.b, 0.5f)),
         phi1(std::exchange(c.phi1, 90.0f * PI / 180.0f)),
         phi2(std::exchange(c.phi2, 270.0f * PI / 180.0f)),
         theta1(std::exchange(c.theta1, 90.0f * PI / 180.0f)),
         theta2(std::exchange(c.theta2, 270.0f * PI / 180.0f)),
         bbox(std::move(c.bbox))
{

}

ConvexPartTorus&
ConvexPartTorus::operator= (const ConvexPartTorus& c) {
    GeometricObject::operator=(c);

    a      = c.a;
    b      = c.b;
    phi1   = c.phi1;
    phi2   = c.phi2;
    theta1 = c.theta1;
    theta2 = c.theta2;
    bbox   = c.bbox;

    return *this;
}

ConvexPartTorus&
ConvexPartTorus::operator= (ConvexPartTorus&& c) noexcept {
    GeometricObject::operator=(std::move(c));

    a      = std::exchange(c.a, 2.0f);
    b      = std::exchange(c.b, 5.0f);
    phi1   = std::exchange(c.phi1, 90.0f * PI / 180.0f);
    phi2   = std::exchange(c.phi2, 270.0f * PI / 180.0f);
    theta1 = std::exchange(c.theta1, 90.0f * PI / 180.0f);
    theta2 = std::exchange(c.theta2, 270.0f * PI / 180.0f);
    bbox   = std::move(c.bbox);

    return *this;
}

ConvexPartTorus*
ConvexPartTorus::clone() const {
    return (new ConvexPartTorus(*this));
}

bool
ConvexPartTorus::hit(const Ray& ray, float& tmin, ShadeRec& sr) const {
    if (!bbox.hit(ray)) {
        return (false);
    }

    float x1 = ray.o.x; float y1 = ray.o.y; float z1 = ray.o.z;
    float d1 = ray.d.x; float d2 = ray.d.y; float d3 = ray.d.z;

    float coeffs[5];    // coefficient array for the quartic equation
    float roots[4];    // solution array for the quartic equation

    // define the coefficients of the quartic equation

    float sum_d_sqrd   = d1 * d1 + d2 * d2 + d3 * d3;
    float e            = x1 * x1 + y1 * y1 + z1 * z1 - a * a - b * b;
    float f            = x1 * d1 + y1 * d2 + z1 * d3;
    float four_a_sqrd  = 4.0 * a * a;

    coeffs[0] = e * e - four_a_sqrd * (b * b - y1 * y1);     // constant term
    coeffs[1] = 4.0 * f * e + 2.0 * four_a_sqrd * y1 * d2;
    coeffs[2] = 2.0 * sum_d_sqrd * e + 4.0 * f * f + four_a_sqrd * d2 * d2;
    coeffs[3] = 4.0 * sum_d_sqrd * f;
    coeffs[4] = sum_d_sqrd * sum_d_sqrd;                      // coefficient of t^4

    // find roots of the quartic equation

    int num_real_roots = SolveQuartic(coeffs, roots);

    bool     intersected    = false;
    float   t              = kHugeValue;
    float   t_t;
    Point3D  p_t;
    Vector3D v_t;
    Vector3D v_t_xz;
    float   phi;
    float   theta;

    if (num_real_roots == 0) {  // ray misses the torus
        return(false);
    }

    // find the smallest root greater than epsilon, if any
    // the roots array is not sorted
    for (int j = 0; j < num_real_roots; j++) {
        if (roots[j] > std::numeric_limits<float>::epsilon()) {
            t_t = roots[j];
            p_t = ray.o + ray.d * t_t;
            v_t = Vector3D(p_t.x, p_t.y, p_t.z);
            v_t_xz = Vector3D(p_t.x, 0.0f, p_t.z);

            v_t_xz.normalize();
            phi = acos((v_t_xz * Vector3D(1.0f, 0.0f, 0.0f)));
            if (v_t_xz.z > 0) {
                phi = TWO_PI - phi;
            }

            theta = acos((v_t.length()*v_t.length() - a*a - b*b) / (2*a*b));
            if (v_t.y < 0) {
                theta = TWO_PI - theta;
            }

            if ((roots[j] < t) &&
                ((theta > theta1) && (theta < theta2)) &&
                (((phi > phi1) && (phi < phi2)) || ((phi + TWO_PI) < phi2))) {
                t = roots[j];
                intersected = true;
            }
        }
    }

    if(!intersected) {
        return (false);
    }

    tmin                  = t;
    sr.local_hit_point     = ray.o + t * ray.d;
    sr.normal              = compute_normal(sr.local_hit_point);
#if 0 // reverse normal for Concave
    sr.normal = -sr.normal;
#endif // 0

    return (true);
}

Normal
ConvexPartTorus::compute_normal(const Point3D& p) const {
    Normal normal;
    float param_squared = a * a + b * b;

    float x = p.x;
    float y = p.y;
    float z = p.z;
    float sum_squared = x * x + y * y + z * z;

    normal.x = 4.0 * x * (sum_squared - param_squared);
    normal.y = 4.0 * y * (sum_squared - param_squared + 2.0 * a * a);
    normal.z = 4.0 * z * (sum_squared - param_squared);
    normal.normalize();

    return (normal);
}
