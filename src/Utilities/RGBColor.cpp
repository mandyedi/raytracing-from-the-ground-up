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

#include "RGBColor.h"

#include <math.h>

RGBColor::RGBColor(float c) : r(c), g(c), b(c) {}

RGBColor::RGBColor(float _r, float _g, float _b) : r(_r), g(_g), b(_b) {}

// used for color filtering in Chapter 28
RGBColor RGBColor::powc(float p) const { return RGBColor(powf(r, p), powf(g, p), powf(b, p)); }

const RGBColor RGBColor::black = RGBColor(0.0f);
const RGBColor RGBColor::white = RGBColor(1.0f);
const RGBColor RGBColor::red = RGBColor(1.0f, 0.0f, 0.0f);
const RGBColor RGBColor::yellow = RGBColor(1.0f, 1.0f, 0.0f);
const RGBColor RGBColor::brown = RGBColor(0.71f, 0.4f, 0.16f);
const RGBColor RGBColor::darkGreen = RGBColor(0.0f, 0.41f, 0.0f);
const RGBColor RGBColor::orange = RGBColor(1.0f, 0.75, 0.0f);
const RGBColor RGBColor::green = RGBColor(0.0f, 0.6f, 0.3f);
const RGBColor RGBColor::lightGreen = RGBColor(0.65f, 1.0f, 0.3f);
const RGBColor RGBColor::darkYellow = RGBColor(0.61f, 0.61f, 0.0f);
const RGBColor RGBColor::lightPurple = RGBColor(0.65f, 0.3f, 1.0f);
const RGBColor RGBColor::darkPurple = RGBColor(0.5f, 0.0f, 1.0f);
const RGBColor RGBColor::grey = RGBColor(0.25f);
