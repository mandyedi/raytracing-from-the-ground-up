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

#ifndef __WRAPPED_TWO_COLORS__
#define __WRAPPED_TWO_COLORS__

#include "Texture.h"
#include "../Utilities/RGBColor.h"

class ShadeRec;
class LatticeNoise;

class WrappedTwoColors: public Texture {
public:

    WrappedTwoColors() = default;

    WrappedTwoColors(LatticeNoise *ln_ptr);

    void set_color1(const float r, const float g, const float b);

    void set_color2(const float r, const float g, const float b);

    void set_min_value(const float min);

    void set_max_value(const float max);

    void set_expansion_value(const float expansion);

    virtual RGBColor get_color(const ShadeRec& sr) const;

private:

    LatticeNoise* noise_ptr = nullptr;
    RGBColor color1 = RGBColor::black;
    RGBColor color2 = RGBColor::darkGreen;
    float min_value = 0.0f;
    float max_value = 1.0f;
    float expansion_number = 2.0;
};

inline void WrappedTwoColors::set_color1(const float r, const float g, const float b) {
    color1.r = r;
    color1.g = g;
    color1.b = b;
}

inline void WrappedTwoColors::set_color2(const float r, const float g, const float b) {
    color2.r = r;
    color2.g = g;
    color2.b = b;
}

inline void WrappedTwoColors::set_min_value(const float min) {
    min_value = min;
}

inline void WrappedTwoColors::set_max_value(const float max) {
    max_value = max;
}

inline void WrappedTwoColors::set_expansion_value(const float expansion) {
    expansion_number = expansion;
}

#endif