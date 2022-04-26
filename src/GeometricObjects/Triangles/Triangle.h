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

#ifndef __TRIANGLE__
#define __TRIANGLE__



#include "../GeometricObject.h"

class Triangle: public GeometricObject {
    public:

        Triangle(void) = default;

        explicit Triangle(const Point3D& a, const Point3D& b, const Point3D& c);

        ~Triangle(void) = default;

        Triangle(const Triangle& triangle);

        Triangle(Triangle&& triangle) noexcept;

        Triangle&
        operator= (const Triangle& triangle);

        Triangle&
        operator= (Triangle&& triangle) noexcept;

        Triangle*
        clone(void) const override;

        BBox
        get_bounding_box(void);

        void
        compute_normal(void);

        bool
        hit(const Ray& ray, float& tmin, ShadeRec& sr) const override;

        bool
        shadow_hit(const Ray& ray, float& tmin) const override;

    private:

        Point3D v0 = Point3D(0.0f, 0.0f, 0.0f);
        Point3D v1 = Point3D(0.0f, 0.0f, 1.0f);
        Point3D v2 = Point3D(1.0f, 0.0f, 0.0f);
        Normal  normal = Normal(0.0f, 1.0f, 0.0f);
};

#endif
