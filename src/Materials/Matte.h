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

#ifndef __MATTE__
#define __MATTE__

#include "../BRDFs/Lambertian.h"
#include "../Materials/Material.h"

class Matte : public Material {
public:

    Matte();

    ~Matte();

    Matte(const Matte& m);

    Matte(Matte&& m) noexcept;

    Matte& operator=(const Matte& m);

    Matte& operator=(Matte&& m) noexcept;

    Material* clone() const override;

    void set_ka(const float k);

    void set_kd(const float k);

    void set_cd(const RGBColor c);

    void set_cd(const float r, const float g, const float b);

    void set_cd(const float c);

    RGBColor shade(ShadeRec& sr) override;

    RGBColor path_shade(ShadeRec& sr) override;

    RGBColor global_shade(ShadeRec& sr);

    RGBColor area_light_shade(ShadeRec& sr) override;

private:

    Lambertian* ambient_brdf = nullptr;
    Lambertian* diffuse_brdf = nullptr;
};

// this sets Lambertian::kd
// there is no Lambertian::ka data member because ambient reflection
// is diffuse reflection

inline void Matte::set_ka(const float ka) { ambient_brdf->set_kd(ka); }

// this also sets Lambertian::kd, but for a different Lambertian object

inline void Matte::set_kd(const float kd) { diffuse_brdf->set_kd(kd); }

inline void Matte::set_cd(const RGBColor c) {
    ambient_brdf->set_cd(c);
    diffuse_brdf->set_cd(c);
}

inline void Matte::set_cd(const float r, const float g, const float b) {
    ambient_brdf->set_cd(r, g, b);
    diffuse_brdf->set_cd(r, g, b);
}

inline void Matte::set_cd(const float c) {
    ambient_brdf->set_cd(c);
    diffuse_brdf->set_cd(c);
}

#endif
