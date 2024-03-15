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

#ifndef __FRESNEL_REFLECTOR__
#define __FRESNEL_REFLECTOR__

class ShadeRec;
class Vector;

#include "BRDF.h"

class FresnelReflector : public BRDF {
public:

    FresnelReflector() = default;

    ~FresnelReflector() = default;

    FresnelReflector(const FresnelReflector& fr);

    FresnelReflector(FresnelReflector&& fr) noexcept;

    FresnelReflector& operator=(const FresnelReflector& fr);

    FresnelReflector& operator=(FresnelReflector&& fr) noexcept;

    FresnelReflector* clone() const override;

    void set_eta_in(const float eta);

    void set_eta_out(const float eta);

    RGBColor sample_f(const ShadeRec& sr, const Vector3D& wo, Vector3D& wr) const override;

private:

    float eta_in = 1.0f;
    float eta_out = 1.0f;

    float fresnel(const ShadeRec& sr) const;
};

inline void FresnelReflector::set_eta_in(const float eta) { eta_in = eta; }

inline void FresnelReflector::set_eta_out(const float eta) { eta_out = eta; }

#endif
