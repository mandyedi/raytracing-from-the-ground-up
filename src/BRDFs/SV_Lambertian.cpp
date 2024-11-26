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

#include "../BRDFs/SV_Lambertian.h"

#include <utility>

#include "../Utilities/Constants.h"

SV_Lambertian::SV_Lambertian(const SV_Lambertian& l) : BRDF(l), kd(l.kd), cd(l.cd) {}

SV_Lambertian::SV_Lambertian(SV_Lambertian&& l) noexcept : BRDF(std::move(l)), kd(std::exchange(l.kd, 0.0f)), cd(std::move(l.cd)) {}

SV_Lambertian& SV_Lambertian::operator=(const SV_Lambertian& l) {
    BRDF::operator=(l);

    kd = l.kd;
    cd = l.cd;

    return *this;
}

SV_Lambertian& SV_Lambertian::operator=(SV_Lambertian&& l) noexcept {
    BRDF::operator=(std::move(l));

    kd = std::exchange(l.kd, 0.0f);
    cd = std::move(l.cd);

    return *this;
}

SV_Lambertian* SV_Lambertian::clone() const {
    return new SV_Lambertian(*this);
}

RGBColor SV_Lambertian::f([[maybe_unused]] const ShadeRec& sr, [[maybe_unused]] const Vector3D& wo, [[maybe_unused]] const Vector3D& wi) const {
    return kd * cd->get_color(sr) * invPI;
}

RGBColor SV_Lambertian::sample_f(const ShadeRec& sr, const Vector3D& wo, Vector3D& wi, float& pdf) const {
    return kd * cd->get_color(sr) * invPI;
}

RGBColor SV_Lambertian::rho([[maybe_unused]] const ShadeRec& sr, [[maybe_unused]] const Vector3D& wo) const {
    return kd * cd->get_color(sr);
}
