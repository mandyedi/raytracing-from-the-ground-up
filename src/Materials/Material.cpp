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

#include "../Materials/Material.h"




Material::Material(const Material& material)
    : shadows(material.shadows)
{}



Material::Material(Material&& material) noexcept
    : shadows(std::exchange(material.shadows, true))
{}



Material&
Material::operator= (const Material& material) {
    shadows = material.shadows;
    return (*this);
}



Material&
Material::operator= (Material&& material) noexcept {
    shadows = std::exchange(material.shadows, true);
    return (*this);
}



Material::~Material(void)
{}



RGBColor
Material::shade([[maybe_unused]] ShadeRec& sr) {
    return (RGBColor::black);
}


RGBColor
Material::area_light_shade(ShadeRec &sr) {
    return shade(sr);
}


RGBColor
Material::get_Le(ShadeRec &sr) const {
    return RGBColor::black;
}
