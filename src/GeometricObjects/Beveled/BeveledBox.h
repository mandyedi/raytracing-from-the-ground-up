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

#ifndef __BEVELED_BOX__
#define __BEVELED_BOX__

#include "../Compound/Compound.h"
#include "../../Utilities/BBox.h"
#include "../../Utilities/Point3D.h"

class BeveledBox: public Compound {
    public:

        BeveledBox(void);

        BeveledBox(const Point3D& min_corner, const Point3D& max_corner, const float bevel_radius);

        ~BeveledBox(void);

        BeveledBox(const BeveledBox& bb);

        BeveledBox(BeveledBox&& bb) noexcept;

        BeveledBox&
        operator= (const BeveledBox& bb);

        BeveledBox&
        operator= (BeveledBox&& bb) noexcept;

        BeveledBox*
        clone(void) const override;

        bool
        shadow_hit(const Ray& ray, float& tmin) const override;

        bool
        hit(const Ray& ray, float& tmin, ShadeRec& sr) const override;

    private:

        Point3D     p0;
        Point3D     p1;
        float       rb;
        BBox        bbox;
};

#endif

