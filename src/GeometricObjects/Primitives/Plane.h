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

#ifndef __PLANE__
#define __PLANE__

#include "../GeometricObject.h"

class Plane : public GeometricObject {
public:

    Plane() = default;

    explicit Plane(const Point3D& point, const Normal& normal);

    ~Plane();

    Plane(const Plane& p);

    Plane(Plane&& p) noexcept;

    Plane& operator=(const Plane& p);

    Plane& operator=(Plane&& p) noexcept;

    Plane* clone() const override;

    bool hit(const Ray& ray, float& tmin, ShadeRec& sr) const override;

    bool shadow_hit(const Ray& ray, float& tmin) const override;

private:

    Point3D a = Point3D(0.0f);            // point through which plane passes
    Normal n = Normal(0.0f, 1.0f, 0.0f);  // normal to the plane

    static const float kEpsilon;  // for shadows and secondary rays
};

#endif
