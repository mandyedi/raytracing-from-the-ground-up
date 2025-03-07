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

#ifndef __WRAPPED_FBM_TEXTURE__
#define __WRAPPED_FBM_TEXTURE__

#include "Texture.h"
#include "../Utilities/RGBColor.h"

class ShadeRec;
class LatticeNoise;

class WrappedFBmTexture: public Texture {
public:

    WrappedFBmTexture() = default;

    WrappedFBmTexture(LatticeNoise *ln_ptr);

    void set_color(const float r, const float g, const float b);

    void set_min_value(const float min);

    void set_max_value(const float max);

    void set_expansion_value(const float expansion);

    virtual RGBColor get_color(const ShadeRec& sr) const;

private:

    LatticeNoise* noise_ptr = nullptr;
    RGBColor color = RGBColor::black;
    float min_value = 0.0f;
    float max_value = 1.0f;
    float expansion_number = 2.0;
};

inline void WrappedFBmTexture::set_color(const float r, const float g, const float b) {
    color.r = r;
    color.g = g;
    color.b = b;
}

inline void WrappedFBmTexture::set_min_value(const float min) {
    min_value = min;
}

inline void WrappedFBmTexture::set_max_value(const float max) {
    max_value = max;
}

inline void WrappedFBmTexture::set_expansion_value(const float expansion) {
    expansion_number = expansion;
}

#endif