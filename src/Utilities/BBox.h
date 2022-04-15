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

#ifndef __BBOX__
#define __BBOX__


#include "Ray.h"
#include "Point3D.h"

class BBox {
    public:
        double x0 = -1.0;
        double x1 = 1.0;
        double y0 = -1.0;
        double y1 = 1.0;
        double z0 = -1.0;
        double z1 = 1.0;

        BBox(void) = default;

        explicit BBox(  const double x0, const double x1,
                const double y0, const double y1,
                const double z0, const double z1);

        explicit BBox(const Point3D p0, const Point3D p1);

        ~BBox(void) = default;

        BBox(const BBox& bbox);

        BBox(BBox&& bbox) noexcept;

        BBox&
        operator= (const BBox& rhs);

        BBox &
        operator= (BBox&& rhs) noexcept;

        bool
        hit(const Ray& ray) const;

        bool
        inside(const Point3D& p) const;
};

#endif
