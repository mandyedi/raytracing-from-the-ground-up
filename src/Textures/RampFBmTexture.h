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

// Marble

#ifndef __RAMP_FBM_TEXTURE__
#define __RAMP_FBM_TEXTURE__

#include "Texture.h"
#include "../Utilities/RGBColor.h"

class ShadeRec;
class Image;
class LatticeNoise;

class RampFBmTexture: public Texture {
public:

    RampFBmTexture() = default;

    RampFBmTexture(Image* r_ptr, LatticeNoise* ln_ptr);

    void set_perturbation(const float p);

    void set_hres(const int h);

    RGBColor get_color(const ShadeRec& sr) const;

    RGBColor get_color2(const ShadeRec &sr) const;

private:

    Image *ramp_ptr;
    LatticeNoise *noise_ptr;
    float perturbation = 3.0f;  // the amount of fbm ("a" in the book)
    int hres;                   // horizontal ramp image resolution
};

inline void RampFBmTexture::set_perturbation(const float p) {
    perturbation = p;
}

inline void RampFBmTexture::set_hres(const int h) {
    hres = h;
}

#endif