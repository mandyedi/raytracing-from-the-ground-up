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

#ifndef __PERFECT_SPECULAR__
#define __PERFECT_SPECULAR__

//     Copyright (C) Kevin Suffern 2000-2007.
//    This C++ code is for non-commercial purposes only.
//    This C++ code is licensed under the GNU General Public License Version 2.
//    See the file COPYING.txt for the full license.


// this implements perfect specular reflection for indirect illumination
// with reflective materials

#include "BRDF.h"

class PerfectSpecular: public BRDF
{
    public:

        PerfectSpecular(void) = default;

        ~PerfectSpecular(void) = default;

        PerfectSpecular(const PerfectSpecular& l);

        PerfectSpecular(PerfectSpecular&& l) noexcept;

        PerfectSpecular&
        operator= (const PerfectSpecular& l);

        PerfectSpecular&
        operator= (PerfectSpecular&& l) noexcept;

        virtual PerfectSpecular*
        clone(void) const;

        void
        set_kr(const float k);

        void
        set_cr(const RGBColor& c);

        void
        set_cr(const float r, const float g, const float b);

        void
        set_cr(const float c);

        virtual RGBColor
        f(const ShadeRec& sr, const Vector3D& wo, const Vector3D& wi) const;

        virtual RGBColor
        sample_f(const ShadeRec& sr, const Vector3D& wo, Vector3D& wi) const;

        virtual RGBColor
        sample_f(const ShadeRec& sr, const Vector3D& wo, Vector3D& wi, float& pdf) const;

        virtual RGBColor
        rho(const ShadeRec& sr, const Vector3D& wo) const;

    private:

        float        kr     = 0.0f;            // reflection coefficient
        RGBColor     cr     = RGBColor::white;            // the reflection colour
};



inline void
PerfectSpecular::set_kr(const float k) {
    kr = k;
}



inline void
PerfectSpecular::set_cr(const RGBColor& c) {
    cr = c;
}



inline void
PerfectSpecular::set_cr(const float r, const float g, const float b) {
    cr.r = r; cr.g = g; cr.b = b;
}



inline void
PerfectSpecular::set_cr(const float c) {
    cr.r = c; cr.g = c; cr.b = c;
}

#endif
