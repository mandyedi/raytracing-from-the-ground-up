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

#include "Matte.h"
#include "../Lights/Light.h"
#include "../Tracers/Tracer.h"


Matte::Matte (void)
    :   Material(),
        ambient_brdf(new Lambertian),
        diffuse_brdf(new Lambertian)
{}



Matte::~Matte(void) {

    if (ambient_brdf != nullptr) {
        delete ambient_brdf;
        ambient_brdf = nullptr;
    }

    if (diffuse_brdf != nullptr) {
        delete diffuse_brdf;
        diffuse_brdf = nullptr;
    }
}



Matte::Matte(const Matte& m)
    :   Material(m)
{
    ambient_brdf = m.ambient_brdf->clone();
    diffuse_brdf = m.diffuse_brdf->clone();
}



Matte::Matte(Matte&& m) noexcept
    :   Material(std::move(m))
{
    ambient_brdf = m.ambient_brdf;
    m.ambient_brdf = nullptr;
    diffuse_brdf = m.diffuse_brdf;
    m.diffuse_brdf = nullptr;
}



Matte&
Matte::operator= (const Matte& m) {
    Material::operator=(m);

    if (ambient_brdf != nullptr) {
        delete ambient_brdf;
    }
    ambient_brdf = m.ambient_brdf->clone();

    if (diffuse_brdf != nullptr) {
        delete diffuse_brdf;
    }
    diffuse_brdf = m.diffuse_brdf->clone();

    return (*this);
}



Matte&
Matte::operator= (Matte&& m) noexcept {
    Material::operator=(std::move(m));

    if (ambient_brdf != nullptr) {
        delete ambient_brdf;
    }
    ambient_brdf = m.ambient_brdf;
    m.ambient_brdf = nullptr;

    if (diffuse_brdf != nullptr) {
        delete diffuse_brdf;
    }
    diffuse_brdf = m.diffuse_brdf;
    m.diffuse_brdf = nullptr;

    return (*this);
}



Material*
Matte::clone(void) const {
    return (new Matte(*this));
}




RGBColor
Matte::shade(ShadeRec& sr) {
    Vector3D    wo          = -sr.ray.d;
    RGBColor    L           = ambient_brdf->rho(sr, wo) * sr.w.ambient_ptr->L(sr);
    size_t      num_lights  = sr.w.lights.size();

    for (size_t j = 0; j < num_lights; j++) {
        Vector3D wi = sr.w.lights[j]->get_direction(sr);
        float ndotwi = sr.normal * wi;

        if (ndotwi > 0.0f) {
            bool in_shadow = false;

            if (sr.w.lights[j]->casts_shadows()) {
                Ray shadowRay(sr.hit_point, wi);
                in_shadow = sr.w.lights[j]->in_shadow(shadowRay, sr);
            }

            if (!in_shadow) {
                L += diffuse_brdf->f(sr, wo, wi) * sr.w.lights[j]->L(sr) * static_cast<float>(ndotwi);
            }
        }
    }

    return (L);
}



RGBColor
Matte::path_shade(ShadeRec& sr) {
    Vector3D    wo = -sr.ray.d;
    Vector3D    wi;
    float       pdf;
    RGBColor    f = diffuse_brdf->sample_f(sr, wo, wi, pdf);
    float       ndotwi = sr.normal * wi;
    Ray         reflected_ray(sr.hit_point, wi);

    return (f * sr.w.tracer_ptr->trace_ray(reflected_ray, sr.depth + 1) * ndotwi / pdf);
}



RGBColor
Matte::global_shade(ShadeRec& sr) {
    RGBColor L;

    if (sr.depth == 0) {
        L = area_light_shade(sr);
    }

    Vector3D    wi;
    Vector3D    wo         = -sr.ray.d;
    float       pdf;
    RGBColor    f          = diffuse_brdf->sample_f(sr, wo, wi, pdf);
    float       ndotwi     = sr.normal * wi;
    Ray         reflected_ray(sr.hit_point, wi);

    L += f * sr.w.tracer_ptr->trace_ray(reflected_ray, sr.depth + 1) * ndotwi / pdf;

    return (L);
}



RGBColor
Matte::area_light_shade(ShadeRec& sr) {
    Vector3D    wo          = -sr.ray.d;
    RGBColor    L           = ambient_brdf->rho(sr, wo) * sr.w.ambient_ptr->L(sr);
    int         num_lights  = sr.w.lights.size();

    for (int j = 0; j < num_lights; j++) {
        Vector3D    wi      = sr.w.lights[j]->get_direction(sr);
        float       ndotwi  = sr.normal * wi;

        if (ndotwi > 0.0f) {
            bool in_shadow = false;

            if (sr.w.lights[j]->casts_shadows()) {
                Ray shadow_ray(sr.hit_point, wi);
                in_shadow = sr.w.lights[j]->in_shadow(shadow_ray, sr);
            }

            if (!in_shadow) {
                L += diffuse_brdf->f(sr, wo, wi) * sr.w.lights[j]->L(sr) * sr.w.lights[j]->G(sr) * ndotwi / sr.w.lights[j]->pdf(sr);
            }
        }
    }

    return (L);
}
