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

#include "GlossyReflector.h"

#include "../Tracers/Tracer.h"

GlossyReflector::~GlossyReflector() {
    if (glossy_specular_brdf != nullptr) {
        delete glossy_specular_brdf;
        glossy_specular_brdf = nullptr;
    }
}

GlossyReflector::GlossyReflector(const GlossyReflector& gr) : Phong(gr) { glossy_specular_brdf = gr.glossy_specular_brdf->clone(); }

GlossyReflector::GlossyReflector(GlossyReflector&& gr) noexcept : Phong(std::move(gr)) {
    glossy_specular_brdf = gr.glossy_specular_brdf->clone();
    gr.glossy_specular_brdf = nullptr;
}

GlossyReflector& GlossyReflector::operator=(const GlossyReflector& gr) {
    Phong::operator=(gr);

    if (glossy_specular_brdf != nullptr) {
        delete glossy_specular_brdf;
    }

    glossy_specular_brdf = gr.glossy_specular_brdf->clone();

    return *this;
}

GlossyReflector& GlossyReflector::operator=(GlossyReflector&& gr) noexcept {
    GlossyReflector::operator=(std::move(gr));

    if (glossy_specular_brdf != nullptr) {
        delete glossy_specular_brdf;
    }
    glossy_specular_brdf = gr.glossy_specular_brdf;
    gr.glossy_specular_brdf = nullptr;

    return *this;
}

GlossyReflector* GlossyReflector::clone() const { return new GlossyReflector(*this); }

RGBColor GlossyReflector::area_light_shade(ShadeRec& sr) {
    RGBColor L(Phong::area_light_shade(sr));  // direct illumination
    Vector3D wo(-sr.ray.d);
    Vector3D wi;
    float pdf;
    RGBColor fr(glossy_specular_brdf->sample_f(sr, wo, wi, pdf));
    Ray reflected_ray(sr.hit_point, wi);

    L += fr * sr.w.tracer_ptr->trace_ray(reflected_ray, sr.depth + 1) * (sr.normal * wi) / pdf;

    return L;
}
