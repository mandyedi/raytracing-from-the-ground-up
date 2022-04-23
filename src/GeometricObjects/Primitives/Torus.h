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

#ifndef __TORUS__
#define __TORUS__

#include "../GeometricObject.h"

class Torus: public GeometricObject {

public:

    Torus();

    explicit Torus(const float _a, const float _b);

    ~Torus() = default;

    Torus(const Torus& t);

    Torus(Torus&& t) noexcept;

    Torus&
    operator= (const Torus& t);

    Torus&
    operator= (Torus&& t) noexcept;

    Normal
    compute_normal(const Point3D& p) const;

    bool
    hit(const Ray& ray, float& tmin, ShadeRec& sr) const override;

private:

    float a;
    float b;
    BBox   bbox;
};

#endif
