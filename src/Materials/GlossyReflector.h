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

#ifndef __GLOSSYREFLECTOR__
#define __GLOSSYREFLECTOR__

#include "../BRDFs/GlossySpecular.h"
#include "Phong.h"

class GlossyReflector : public Phong {
public:

    GlossyReflector() = default;

    ~GlossyReflector();

    GlossyReflector(const GlossyReflector& gr);

    GlossyReflector(GlossyReflector&& gr) noexcept;

    GlossyReflector& operator=(const GlossyReflector& gr);

    GlossyReflector& operator=(GlossyReflector&& gr) noexcept;

    GlossyReflector* clone(void) const override;

    void set_samples(const int num_samples, const float exp);

    void set_kr(const float k);

    void set_exponent(const float exp);

    // TODO: ???
    // virtual RGBColor
    // shade(ShadeRec &sr) override;

    virtual RGBColor area_light_shade(ShadeRec& sr) override;

private:

    GlossySpecular* glossy_specular_brdf = new GlossySpecular;
};

inline void GlossyReflector::set_samples(const int num_samples, const float exp) { glossy_specular_brdf->set_samples(num_samples, exp); }

inline void GlossyReflector::set_kr(const float k) { glossy_specular_brdf->set_ks(k); }

inline void GlossyReflector::set_exponent(const float exp) { glossy_specular_brdf->set_exp(exp); }

#endif
