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

#include "Phong.h"


Phong::Phong (void)
    :   Material(),
        ambient_brdf(new Lambertian),
        diffuse_brdf(new Lambertian),
        specular_brdf(new GlossySpecular)
{}



Phong::~Phong(void) {

    if (ambient_brdf != nullptr) {
        delete ambient_brdf;
        ambient_brdf = nullptr;
    }

    if (diffuse_brdf != nullptr) {
        delete diffuse_brdf;
        diffuse_brdf = nullptr;
    }

    if (specular_brdf != nullptr) {
        delete specular_brdf;
        specular_brdf = nullptr;
    }
}



Phong::Phong(const Phong& p)
    :   Material(p)
{
    ambient_brdf = p.ambient_brdf->clone();
    diffuse_brdf = p.diffuse_brdf->clone();
    specular_brdf = p.specular_brdf->clone();
}



Phong::Phong(Phong&& p) noexcept
    :   Material(std::move(p))
{
    ambient_brdf = p.ambient_brdf;
    p.ambient_brdf = nullptr;
    diffuse_brdf = p.diffuse_brdf;
    p.diffuse_brdf = nullptr;
    specular_brdf = p.specular_brdf;
    p.specular_brdf = nullptr;
}



Phong&
Phong::operator= (const Phong& p) {
    Material::operator=(p);

    if (ambient_brdf != nullptr) {
        delete ambient_brdf;
    }
    ambient_brdf = p.ambient_brdf->clone();

    if (diffuse_brdf != nullptr) {
        delete diffuse_brdf;
    }
    diffuse_brdf = p.diffuse_brdf->clone();

    if (specular_brdf != nullptr) {
        delete specular_brdf;
    }
    specular_brdf = p.specular_brdf->clone();

    return (*this);
}



Phong&
Phong::operator= (Phong&& p) noexcept {
    Material::operator=(std::move(p));

    if (ambient_brdf != nullptr) {
        delete ambient_brdf;
    }
    ambient_brdf = p.ambient_brdf;
    p.ambient_brdf = nullptr;

    if (diffuse_brdf != nullptr) {
        delete diffuse_brdf;
    }
    diffuse_brdf = p.diffuse_brdf;
    p.diffuse_brdf = nullptr;

    if (specular_brdf != nullptr) {
        delete specular_brdf;
    }
    specular_brdf = p.specular_brdf;
    p.specular_brdf = nullptr;

    return (*this);
}



Material*
Phong::clone(void) const {
    return (new Phong(*this));
}



RGBColor
Phong::shade(ShadeRec& sr) {
    Vector3D wo = -sr.ray.d;
    RGBColor L = ambient_brdf->rho(sr, wo) * sr.w.ambient_ptr->L(sr);
    int num_lights = sr.w.lights.size();

    for (int j = 0; j < num_lights; j++) {
        Vector3D wi = sr.w.lights[j]->get_direction(sr);
        float ndotwi = sr.normal * wi;

        if (ndotwi > 0.0f) {
            bool in_shadow = false;

            if (sr.w.lights[j]->casts_shadows()) {
                Ray shadowRay(sr.hit_point, wi);
                in_shadow = sr.w.lights[j]->in_shadow(shadowRay, sr);
            }

            if (!in_shadow) {
                L += ( diffuse_brdf->f(sr, wo, wi) + specular_brdf->f(sr, wo, wi) ) * sr.w.lights[j]->L(sr) * ndotwi;
            }
        }
    }

    return (L);
}



RGBColor
Phong::area_light_shade(ShadeRec &sr) {
    Vector3D wo = -sr.ray.d;
    RGBColor L = ambient_brdf->rho(sr, wo) * sr.w.ambient_ptr->L(sr);
    int num_lights = sr.w.lights.size();

    for (int j = 0; j < num_lights; j++) {
        Vector3D wi = sr.w.lights[j]->get_direction(sr);
        float ndotwi = sr.normal * wi;

        if (ndotwi > 0.0){
            bool in_shadow = false;

            if (sr.w.lights[j]->casts_shadows()) {
                Ray shadowRay(sr.hit_point, wi);
                in_shadow = sr.w.lights[j]->in_shadow(shadowRay, sr);
            }

            if (!in_shadow){
                L += ( diffuse_brdf->f(sr, wo, wi) + specular_brdf->f(sr, wo, wi) )
                        * sr.w.lights[j]->L(sr) * sr.w.lights[j]->G(sr) * ndotwi / sr.w.lights[j]->pdf(sr);
            }
        }
    }

    return (L);
}