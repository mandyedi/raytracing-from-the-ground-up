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

#include "Transparent.h"

#include "../BRDFs/PerfectSpecular.h"
#include "../BTDFs/PerfectTransmitter.h"
#include "../Tracers/Tracer.h"

Transparent::Transparent() : Phong(), reflective_brdf(new PerfectSpecular), specular_btdf(new PerfectTransmitter) {}

Transparent::~Transparent() {
    if (reflective_brdf != nullptr) {
        delete reflective_brdf;
        reflective_brdf = nullptr;
    }

    if (specular_btdf != nullptr) {
        delete specular_btdf;
        specular_btdf = nullptr;
    }
}

Transparent::Transparent(const Transparent& tr) : Phong(tr) {
    reflective_brdf = tr.reflective_brdf->clone();
    specular_btdf = tr.specular_btdf->clone();
}

Transparent::Transparent(Transparent&& tr) noexcept : Phong(std::move(tr)), reflective_brdf(std::move(tr.reflective_brdf)), specular_btdf(std::move(tr.specular_btdf)) {}

Transparent& Transparent::operator=(const Transparent& tr) {
    Phong::operator=(tr);

    if (reflective_brdf != nullptr) {
        delete reflective_brdf;
    }
    reflective_brdf = tr.reflective_brdf->clone();

    if (specular_btdf != nullptr) {
        delete specular_btdf;
    }
    specular_btdf = tr.specular_btdf->clone();

    return *this;
}

Transparent& Transparent::operator=(Transparent&& tr) noexcept {
    Phong::operator=(std::move(tr));

    if (reflective_brdf != nullptr) {
        delete reflective_brdf;
    }
    reflective_brdf = tr.reflective_brdf;
    tr.reflective_brdf = nullptr;

    if (specular_btdf != nullptr) {
        delete specular_btdf;
    }
    specular_btdf = tr.specular_btdf;
    tr.specular_btdf = nullptr;

    return *this;
}

Transparent* Transparent::clone() const { return new Transparent(*this); }

RGBColor Transparent::shade(ShadeRec& sr) {
    RGBColor L(Phong::shade(sr));

    Vector3D wo = -sr.ray.d;
    Vector3D wi;
    RGBColor fr = reflective_brdf->sample_f(sr, wo, wi);
    Ray reflected_ray(sr.hit_point, wi);

    if (specular_btdf->tir(sr)) {
        L += sr.w.tracer_ptr->trace_ray(reflected_ray, sr.depth + 1);
    } else {
        Vector3D wt;
        RGBColor ft = specular_btdf->sample_f(sr, wo, wt);
        Ray transmitted_ray(sr.hit_point, wt);

        L += fr * sr.w.tracer_ptr->trace_ray(reflected_ray, sr.depth + 1) * fabs(sr.normal * wi);
        L += ft * sr.w.tracer_ptr->trace_ray(transmitted_ray, sr.depth + 1) * fabs(sr.normal * wt);
    }

    return L;
}
