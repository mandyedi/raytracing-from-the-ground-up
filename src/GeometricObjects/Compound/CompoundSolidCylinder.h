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

#ifndef __COMPOUNDSOLIDCYLINDER__
#define __COMPOUNDSOLIDCYLINDER__

#include "Compound.h"

class CompoundSolidCylinder : public Compound {
public:

    CompoundSolidCylinder();

    CompoundSolidCylinder(const float bottom, const float top, const float radius);

    ~CompoundSolidCylinder();

    CompoundSolidCylinder(const CompoundSolidCylinder& sc);

    CompoundSolidCylinder(CompoundSolidCylinder&& sc) noexcept;

    CompoundSolidCylinder& operator=(const CompoundSolidCylinder& sc);

    CompoundSolidCylinder& operator=(CompoundSolidCylinder&& sc) noexcept;

    virtual CompoundSolidCylinder* clone() const;

    virtual bool hit(const Ray& ray, float& tmin, ShadeRec& s) const;

    virtual bool shadow_hit(const Ray& ray, float& tmin) const;

private:

    BBox bbox;
};

#endif
