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


#include <utility>
#include "Light.h"
#include "../Utilities/RGBColor.h"


Light::~Light(void) {}



Light::Light(const Light& l)
    : shadows(l.shadows)
{}



Light::Light(Light&& l) noexcept
    : shadows(std::exchange(l.shadows, false))
{}



Light&
Light::operator= (const Light& l) {
    shadows = l.shadows;

    return (*this);
}



Light&
Light::operator= (Light&& l) noexcept {
    shadows = std::exchange(l.shadows, false);

    return (*this);
}



RGBColor
Light::L([[maybe_unused]] ShadeRec& s) {
    return (RGBColor::black);
}


bool
Light::in_shadow(const Ray &ray, const ShadeRec &sr) const{
    return false;
}

float
Light::G(const ShadeRec& sr) const {
    return 1.0f;
};

float
Light::pdf(const ShadeRec &sr) const {
    return 1.0;
}