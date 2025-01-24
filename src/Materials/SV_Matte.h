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

#ifndef __SV_MATTE__
#define __SV_MATTE__

#include "../BRDFs/SV_Lambertian.h"
#include "../Materials/Material.h"

class SV_Matte : public Material {
public:

    SV_Matte();

    ~SV_Matte();

    SV_Matte(const SV_Matte& m);

    SV_Matte(SV_Matte&& m) noexcept;

    SV_Matte& operator=(const SV_Matte& m);

    SV_Matte& operator=(SV_Matte&& m) noexcept;

    Material* clone() const override;

    void set_ka(const float k);

    void set_kd(const float k);

    void set_cd(const Texture* texture_ptr);

    RGBColor shade(ShadeRec& sr) override;

    RGBColor path_shade(ShadeRec& sr) override;

    RGBColor global_shade(ShadeRec& sr);

    RGBColor area_light_shade(ShadeRec& sr) override;

private:

    SV_Lambertian* ambient_brdf = nullptr;
    SV_Lambertian* diffuse_brdf = nullptr;
};

// this sets Lambertian::kd
// there is no Lambertian::ka data member because ambient reflection
// is diffuse reflection

inline void SV_Matte::set_ka(const float ka) { ambient_brdf->set_kd(ka); }

// this also sets Lambertian::kd, but for a different Lambertian object

inline void SV_Matte::set_kd(const float kd) { diffuse_brdf->set_kd(kd); }

inline void SV_Matte::set_cd(const Texture *texture_ptr) {
    ambient_brdf->set_cd(texture_ptr);
    diffuse_brdf->set_cd(texture_ptr);
}

#endif
