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

#include "Reflective.h"
#include "../Tracers/Tracer.h"


Reflective::~Reflective(void) {
    if (reflective_brdf != nullptr) {
        delete reflective_brdf;
        reflective_brdf = nullptr;
    }
}



Reflective::Reflective(const Reflective& r)
    :     Phong(r) {
        reflective_brdf = r.reflective_brdf->clone();
}



Reflective::Reflective(Reflective&& r) noexcept
    :     Phong(std::move(r)) {
    reflective_brdf = r.reflective_brdf->clone();
    r.reflective_brdf = nullptr;
}



Reflective&
Reflective::operator= (const Reflective& r) {
    Phong::operator=(r);

    if (reflective_brdf != nullptr) {
        delete reflective_brdf;
    }

    reflective_brdf = r.reflective_brdf->clone();

    return (*this);
}



Reflective&
Reflective::operator= (Reflective&& r) noexcept {
    Phong::operator=(std::move(r));

    if (reflective_brdf != nullptr) {
        delete reflective_brdf;
    }
    reflective_brdf = r.reflective_brdf;
    r.reflective_brdf = nullptr;

    return (*this);
}



Reflective*
Reflective::clone(void) const {
    return (new Reflective(*this));
}



RGBColor
Reflective::shade(ShadeRec& sr) {
    RGBColor L(Phong::shade(sr));  // direct illumination

    Vector3D wo = -sr.ray.d;
    Vector3D wi;
    RGBColor fr = reflective_brdf->sample_f(sr, wo, wi);
    Ray reflected_ray(sr.hit_point, wi);

    L += fr * sr.w.tracer_ptr->trace_ray(reflected_ray, sr.depth + 1) * (sr.normal * wi);

    return (L);
}



RGBColor
Reflective::path_shade(ShadeRec& sr) {
    Vector3D    wo = -sr.ray.d;
    Vector3D    wi;
    float       pdf;
    RGBColor    fr = reflective_brdf->sample_f(sr, wo, wi, pdf);
    Ray         reflected_ray(sr.hit_point, wi);

    return (fr * sr.w.tracer_ptr->trace_ray(reflected_ray, sr.depth + 1) * (sr.normal * wi) / pdf);
}



RGBColor
Reflective::global_shade(ShadeRec& sr) {
    Vector3D    wo = -sr.ray.d;
    Vector3D    wi;
    float       pdf;
    RGBColor    fr = reflective_brdf->sample_f(sr, wo, wi, pdf);
    Ray         reflected_ray(sr.hit_point, wi);

    if (sr.depth == 0) {
        return (fr * sr.w.tracer_ptr->trace_ray(reflected_ray, sr.depth + 2) * (sr.normal * wi) / pdf);
    }
    else {
        return (fr * sr.w.tracer_ptr->trace_ray(reflected_ray, sr.depth + 1) * (sr.normal * wi) / pdf);
    }
}
