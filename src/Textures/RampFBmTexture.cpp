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

#include "RampFBmTexture.h"
#include "../Utilities/Image.h"
#include "../Noises/LatticeNoise.h"

RampFBmTexture::RampFBmTexture(Image *r_ptr, LatticeNoise *ln_ptr) {
    ramp_ptr = r_ptr;
    noise_ptr = ln_ptr;
}

RGBColor RampFBmTexture::get_color(const ShadeRec& sr) const {
    float     y = sr.local_hit_point.y;
    float     u = (1.0 + sin(y)) / 2.0;
    int     row = 0;    // use top row of ramp image
    int     column = (int)(u * (ramp_ptr->get_hres() - 1));

    return ramp_ptr->get_color(row, column);
}


RGBColor RampFBmTexture::get_color2(const ShadeRec &sr) const {
    float noise = noise_ptr->value_fbm(sr.local_hit_point);
    float y = sr.local_hit_point.y + perturbation * noise;
    float u = (1.0 + sin(y)) / 2.0;
    int row = 0;    // use top row of ramp image
    int column = (int)(u * (hres - 1));

    return ramp_ptr->get_color(row, column);
}