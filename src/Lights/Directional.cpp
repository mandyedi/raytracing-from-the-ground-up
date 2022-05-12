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

#include "Directional.h"

#include "../GeometricObjects/GeometricObject.h"

Directional::Directional(const Directional& dl) : Light(dl), ls(dl.ls), color(dl.color), dir(dl.dir) {}

Directional::Directional(Directional&& dl) noexcept : Light(std::move(dl)), ls(std::exchange(dl.ls, 1.0f)), color(std::move(dl.color)), dir(std::move(dl.dir)) {}

Directional& Directional::operator=(const Directional& dl) {
    Light::operator=(dl);

    ls = dl.ls;
    color = dl.color;
    dir = dl.dir;

    return (*this);
}

Directional& Directional::operator=(Directional&& dl) noexcept {
    Light::operator=(std::move(dl));

    ls = std::exchange(dl.ls, 1.0f);
    color = std::move(dl.color);
    dir = std::move(dl.dir);

    return (*this);
}

Light* Directional::clone(void) const { return (new Directional(*this)); }

Directional::~Directional(void) {}

Vector3D Directional::get_direction([[maybe_unused]] ShadeRec& sr) { return (dir); }

RGBColor Directional::L([[maybe_unused]] ShadeRec& s) { return (ls * color); }

bool Directional::in_shadow(const Ray& ray, const ShadeRec& sr) const {
    float t;
    int num_objects = sr.w.objects.size();

    for (int j = 0; j < num_objects; j++) {
        if (sr.w.objects[j]->shadow_hit(ray, t) && t > 0) {
            return true;
        }
    }

    return false;
}
