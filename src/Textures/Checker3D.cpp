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
#include <cmath>
#include "Checker3D.h"
#include "../Utilities/Constants.h"
#include "../Utilities/RGBColor.h"

Checker3D::~Checker3D(void) {}

Checker3D::Checker3D(const Checker3D& c)
    : Texture(c),
      color1(c.color1),
      color2(c.color2),
      size(c.size)
{}

Checker3D::Checker3D(Checker3D&& c) noexcept
    : Texture(std::move(c)),
      color1(std::move(c.color1)),
      color2(std::move(c.color2)),
      size(std::exchange(c.size, 0.0f))
{}

Checker3D&
Checker3D::operator= (const Checker3D& c) {
    Texture::operator=(c);

    color1      = c.color1;
    color2      = c.color2;
    size        = c.size;

    return (*this);
}

Checker3D&
Checker3D::operator= (Checker3D&& c) noexcept {
    Texture::operator=(std::move(c));

    color1      = std::move(c.color1);
    color2      = std::move(c.color2);
    size        = std::exchange(c.size, 0);

    return (*this);
}

Checker3D*
Checker3D::clone(void) const {
    return (new Checker3D(*this));
}

RGBColor
Checker3D::get_color(const ShadeRec& sr) const {
    float eps = -0.000187453738;   // small random number
    float x = sr.local_hit_point.x + eps;
    float y = sr.local_hit_point.y + eps;
    float z = sr.local_hit_point.z + eps;

    if (((int)floor(x / size) + (int)floor(y / size) + (int)floor(z / size)) % 2 == 0) {
        return (color1);
    }
    else {
        return (color2);
    }
}
