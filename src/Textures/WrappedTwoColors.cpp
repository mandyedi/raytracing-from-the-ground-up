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

#include <cmath>

#include "WrappedTwoColors.h"
#include "../Noises/LatticeNoise.h"

WrappedTwoColors::WrappedTwoColors(LatticeNoise *ln_ptr) {
    noise_ptr = ln_ptr;
}

RGBColor WrappedTwoColors::get_color(const ShadeRec& sr) const {
    float noise = expansion_number * noise_ptr->value_fbm(sr.local_hit_point);
    float value = noise - floor(noise);
    value = min_value + (max_value - min_value) * value;

    if (noise < 1.0) {
        return (value * color1);
    }
    else {
        return (value * color2);
    }
}
