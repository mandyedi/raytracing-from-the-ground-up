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

#ifndef __BOX__
#define __BOX__

#include "../../Utilities/Point3D.h"
#include "../../Utilities/Ray.h"
#include "../GeometricObject.h"

class ShadeRec;

class Box : public GeometricObject {
public:

    float x0 = -1.0f;
    float x1 = 1.0f;
    float y0 = -1.0f;
    float y1 = 1.0f;
    float z0 = -1.0f;
    float z1 = 1.0f;

    Box() = default;

    explicit Box(const float x0, const float x1, const float y0, const float y1, const float z0, const float z1);

    explicit Box(const Point3D p0, const Point3D p1);

    ~Box() = default;

    Box(const Box& box);

    Box(Box&& box) noexcept;

    Box& operator=(const Box& box);

    Box& operator=(Box&& box) noexcept;

    Box* clone() const override;

    bool hit(const Ray& ray, float& tmin, ShadeRec& sr) const;

    bool inside(const Point3D& point) const;

private:

    Normal get_normal(const int face_hit) const;
};

#endif
