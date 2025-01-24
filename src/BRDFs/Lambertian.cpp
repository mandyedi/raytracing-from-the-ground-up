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

#include "../BRDFs/Lambertian.h"

#include <utility>

#include "../Utilities/Constants.h"

Lambertian::Lambertian(const Lambertian& l) : BRDF(l), kd(l.kd), cd(l.cd) {}

Lambertian::Lambertian(Lambertian&& l) noexcept : BRDF(std::move(l)), kd(std::exchange(l.kd, 0.0f)), cd(std::move(l.cd)) {}

Lambertian& Lambertian::operator=(const Lambertian& l) {
    BRDF::operator=(l);

    kd = l.kd;
    cd = l.cd;

    return *this;
}

Lambertian& Lambertian::operator=(Lambertian&& l) noexcept {
    BRDF::operator=(std::move(l));

    kd = std::exchange(l.kd, 0.0f);
    cd = std::move(l.cd);

    return *this;
}

Lambertian* Lambertian::clone() const { return new Lambertian(*this); }

RGBColor Lambertian::f([[maybe_unused]] const ShadeRec& sr, [[maybe_unused]] const Vector3D& wo, [[maybe_unused]] const Vector3D& wi) const { return kd * cd * invPI; }

// this generates a direction by sampling the hemisphere with a cosine distribution
// this is called in path_shade for any material with a diffuse shading component
// the samples have to be stored with a cosine distribution

RGBColor Lambertian::sample_f(const ShadeRec& sr, const Vector3D& wo, Vector3D& wi, float& pdf) const {
    Vector3D w(sr.normal);
    Vector3D v = Vector3D(0.0034f, 1.0f, 0.0071f) ^ w;
    v.normalize();
    Vector3D u = v ^ w;

    Point3D sp = sampler_ptr->sample_hemisphere();
    wi = sp.x * u + sp.y * v + sp.z * w;
    wi.normalize();

    pdf = sr.normal * wi * invPI;

    return kd * cd * invPI;
}

RGBColor Lambertian::rho([[maybe_unused]] const ShadeRec& sr, [[maybe_unused]] const Vector3D& wo) const { return kd * cd; }
