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

#include "Emissive.h"



Emissive::~Emissive(void) {}



Emissive::Emissive(const Emissive& m)
    :   Material(m),
        ls(m.ls),
        ce(m.ce)
{}



Emissive::Emissive(Emissive&& m) noexcept
    :   Material(std::move(m)),
        ls(std::exchange(m.ls, 1.0f)),
        ce(std::move(m.ce))
{}



Emissive&
Emissive::operator= (const Emissive& e) {
    Material::operator=(e);

    ls = e.ls;
    ce = e.ce;

    return (*this);
}



Emissive&
Emissive::operator= (Emissive&& e) noexcept {
    Material::operator=(std::move(e));

    ls = std::exchange(e.ls, 1.0f);
    ce = std::move(e.ce);

    return (*this);
}



Material*
Emissive::clone(void) const {
    return (new Emissive(*this));
}



RGBColor
Emissive::area_light_shade(ShadeRec& sr) {
    if (-sr.normal * sr.ray.d > 0.0) {
        return (ls * ce);
    }
    else {
        return (RGBColor::black);
    }
}