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

#include "AreaLight.h"

AreaLight::~AreaLight() {
    if (object_ptr != nullptr) {
        delete object_ptr;
        object_ptr = nullptr;
    }

    if (material_ptr != nullptr) {
        delete material_ptr;
        material_ptr = nullptr;
    }
}

AreaLight::AreaLight(const AreaLight& al) : Light(al), object_ptr(al.object_ptr), material_ptr(al.material_ptr), sample_point(al.sample_point), light_normal(al.light_normal), wi(al.wi) {
    object_ptr = al.object_ptr->clone();
    material_ptr = al.material_ptr->clone();
}

AreaLight::AreaLight(AreaLight&& al) noexcept
    : Light(std::move(al)),
      object_ptr(std::move(al.object_ptr)),
      material_ptr(std::move(al.material_ptr)),
      sample_point(std::move(al.sample_point)),
      light_normal(std::move(al.light_normal)),
      wi(std::move(al.wi)) {
    object_ptr = al.object_ptr->clone();
    material_ptr = al.material_ptr->clone();
}

AreaLight& AreaLight::operator=(const AreaLight& al) {
    Light::operator=(al);

    if (object_ptr != nullptr) {
        delete object_ptr;
    }

    object_ptr = al.object_ptr->clone();

    if (material_ptr != nullptr) {
        delete material_ptr;
    }

    material_ptr = al.material_ptr->clone();

    sample_point = al.sample_point;
    light_normal = al.light_normal;
    wi = al.wi;

    return *this;
}

AreaLight& AreaLight::operator=(AreaLight&& al) noexcept {
    Light::operator=(std::move(al));

    if (object_ptr != nullptr) {
        delete object_ptr;
    }

    object_ptr = al.object_ptr;
    al.object_ptr = nullptr;

    if (material_ptr != nullptr) {
        delete material_ptr;
    }

    material_ptr = al.material_ptr;
    al.material_ptr = nullptr;

    sample_point = std::move(al.sample_point);
    light_normal = std::move(al.light_normal);
    wi = std::move(al.wi);

    return *this;
}

AreaLight* AreaLight::clone() const { return new AreaLight(*this); }

Vector3D AreaLight::get_direction(ShadeRec& sr) {
    sample_point = object_ptr->sample();  // used in the G function
    light_normal = object_ptr->get_normal(sample_point);
    wi = sample_point - sr.hit_point;  // used in the G function
    wi.normalize();

    return wi;
}

RGBColor AreaLight::L(ShadeRec& sr) {
    float ndotd = -light_normal * wi;

    if (ndotd > 0.0f) {
        return material_ptr->get_Le(sr);
    } else {
        return RGBColor::black;
    }
}

bool AreaLight::in_shadow(const Ray& ray, const ShadeRec& sr) const {
    float t;
    int num_objects = sr.w.objects.size();
    float ts = (sample_point - ray.o) * ray.d;

    for (int j = 0; j < num_objects; j++) {
        if (sr.w.objects[j]->shadow_hit(ray, t) && t < ts) {
            return true;
        }
    }

    return false;
}

// G is part of the geometric factor

float AreaLight::G(const ShadeRec& sr) const {
    float ndotd = -light_normal * wi;
    float d2 = sample_point.d_squared(sr.hit_point);

    return ndotd / d2;
}

float AreaLight::pdf(const ShadeRec& sr) const { return object_ptr->pdf(sr); }
