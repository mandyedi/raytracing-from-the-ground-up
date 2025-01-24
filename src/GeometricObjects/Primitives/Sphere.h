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

#ifndef __SPHERE__
#define __SPHERE__

#include "../GeometricObject.h"

class Sphere : public GeometricObject {
public:

    Sphere() = default;

    explicit Sphere(const Point3D& center, float r);

    ~Sphere();

    Sphere(const Sphere& s);

    Sphere(Sphere&& s) noexcept;

    Sphere& operator=(const Sphere& s);

    Sphere& operator=(Sphere&& s) noexcept;

    Sphere* clone() const override;

    void set_center(const Point3D& c);

    void set_center(const float x, const float y, const float z);

    void set_radius(const float r);

    bool hit(const Ray& ray, float& t, ShadeRec& s) const override;

    bool shadow_hit(const Ray& ray, float& tmin) const override;

private:

    Point3D center = Point3D(0.0f);
    float radius = 1.0f;

    static const float kEpsilon;  // for shadows and secondary rays
};

inline void Sphere::set_center(const Point3D& c) { center = c; }

inline void Sphere::set_center(const float x, const float y, const float z) {
    center.x = x;
    center.y = y;
    center.z = z;
}

inline void Sphere::set_radius(const float r) { radius = r; }

#endif
