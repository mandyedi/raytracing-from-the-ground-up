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

#ifndef __DISK__
#define __DISK__

#include "../GeometricObject.h"

class Disk : public GeometricObject {
public:

    Disk(void) = default;

    explicit Disk(const Point3D& p, const Normal& n, float r);

    ~Disk(void) = default;

    Disk(const Disk& r);

    Disk(Disk&& r) noexcept;

    Disk& operator=(const Disk& rhs);

    Disk& operator=(Disk&& rhs) noexcept;

    Disk* clone(void) const override;

    bool hit(const Ray& ray, float& t, ShadeRec& s) const;

private:

    Point3D center = Point3D(0.0f);
    Normal normal = Normal(0.0f, 1.0f, 0.0f);
    float r_squared = 1.0f;

    static const float kEpsilon;
};

#endif
