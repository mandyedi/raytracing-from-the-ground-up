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

#ifndef __SV_LAMBERTIAN__
#define __SV_LAMBERTIAN__

#include "BRDF.h"
#include "../Textures/Texture.h"

class SV_Lambertian : public BRDF {
public:

    SV_Lambertian() = default;

    ~SV_Lambertian() = default;

    SV_Lambertian(const SV_Lambertian& l);

    SV_Lambertian(SV_Lambertian&& l) noexcept;

    SV_Lambertian& operator=(const SV_Lambertian& l);

    SV_Lambertian& operator=(SV_Lambertian&& l) noexcept;

    SV_Lambertian* clone() const override;

    RGBColor f(const ShadeRec& sr, const Vector3D& wo, const Vector3D& wi) const override;

    RGBColor sample_f(const ShadeRec& sr, const Vector3D& wo, Vector3D& wi, float& pdf) const override;

    RGBColor rho(const ShadeRec& sr, const Vector3D& wo) const override;

    void set_ka(const float ka);

    void set_kd(const float kd);

    void set_cd(const Texture* texture_ptr);

private:

    float kd = 0.0f;
    Texture* cd = nullptr;
};

inline void SV_Lambertian::set_ka(const float k) { kd = k; }

inline void SV_Lambertian::set_kd(const float k) { kd = k; }

inline void SV_Lambertian::set_cd(const Texture *texture_ptr) {
    if (cd) {
        delete cd;
        cd = nullptr;
    }

    if (texture_ptr) {
        cd = texture_ptr->clone();
    }
}

#endif
