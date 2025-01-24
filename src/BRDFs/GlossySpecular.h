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

#ifndef __GLOSSY_SPECULAR__
#define __GLOSSY_SPECULAR__

#include "BRDF.h"

class GlossySpecular : public BRDF {
public:

    GlossySpecular() = default;

    ~GlossySpecular();

    GlossySpecular(const GlossySpecular& gs);

    GlossySpecular(GlossySpecular&& gs) noexcept;

    GlossySpecular& operator=(const GlossySpecular& gs);

    GlossySpecular& operator=(GlossySpecular&& gs) noexcept;

    GlossySpecular* clone() const override;

    RGBColor f(const ShadeRec& sr, const Vector3D& wo, const Vector3D& wi) const override;

    RGBColor sample_f(const ShadeRec& sr, const Vector3D& wo, Vector3D& wi, float& pdf) const override;

    RGBColor rho(const ShadeRec& sr, const Vector3D& wo) const override;

    void set_ks(const float ks);

    void set_exp(const float exp);

    void set_cs(const RGBColor& c);

    void set_cs(const float r, const float g, const float b);

    void set_cs(const float c);

    void set_sampler(Sampler* sp, const float exp);

    void set_samples(const int num_samples, const float exp);

private:

    float ks = 0.0f;
    RGBColor cs = RGBColor::white;   // specular color
    float exp = 0.0f;                // specular exponent
    Sampler* sampler_ptr = nullptr;  // for use in sample_f
};

inline void GlossySpecular::set_ks(const float k) { ks = k; }

inline void GlossySpecular::set_exp(const float e) { exp = e; }

inline void GlossySpecular::set_cs(const RGBColor& c) { cs = c; }

inline void GlossySpecular::set_cs(const float r, const float g, const float b) {
    cs.r = r;
    cs.g = g;
    cs.b = b;
}

inline void GlossySpecular::set_cs(const float c) {
    cs.r = c;
    cs.g = c;
    cs.b = c;
}

#endif
