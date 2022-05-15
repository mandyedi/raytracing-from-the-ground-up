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

#ifndef __BTDF__
#define __BTDF__

#include "../Utilities/RGBColor.h"

class ShadeRec;
class Vector3D;

class BTDF {
public:

    BTDF() = default;

    virtual ~BTDF() = default;

    BTDF(const BTDF& btdf) = default;

    BTDF(BTDF&& btdf) = default;

    BTDF& operator=(const BTDF& btdf) = default;

    BTDF& operator=(BTDF&& btdf) = default;

    virtual BTDF* clone() = 0;

    virtual RGBColor f(const ShadeRec& sr, const Vector3D& wo, const Vector3D& wi) const;

    virtual RGBColor sample_f(const ShadeRec& sr, const Vector3D& wo, Vector3D& wt) const;

    virtual RGBColor rho(const ShadeRec& sr, const Vector3D& wo) const;
};

#endif
