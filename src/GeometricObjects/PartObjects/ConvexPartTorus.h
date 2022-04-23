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

#ifndef __CONVEXPARTTORUS__
#define __CONVEXPARTTORUS__

#include "../GeometricObject.h"


class ConvexPartTorus: public GeometricObject {

public:

    ConvexPartTorus();

    explicit ConvexPartTorus(const float _a,      const float _b,
                             const float _phi1,   const float _phi2,
                             const float _theta1, const float _theta2);

    ~ConvexPartTorus() = default;

    ConvexPartTorus(const ConvexPartTorus& c);

    ConvexPartTorus(ConvexPartTorus&& c) noexcept;

    ConvexPartTorus&
    operator= (const ConvexPartTorus& c);

    ConvexPartTorus&
    operator= (ConvexPartTorus&& c) noexcept;

    ConvexPartTorus*
    clone() const override;

    bool
    hit(const Ray& ray, float& tmin, ShadeRec& sr) const override;

private:

    float a;
    float b;
    float phi1;
    float phi2;
    float theta1;
    float theta2;
    BBox   bbox;

    Normal
    compute_normal(const Point3D& p) const;
};

#endif
