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

#ifndef __PLANE_CHECKER__
#define __PLANE_CHECKER__

#include "Texture.h"
#include "../Utilities/RGBColor.h"

// For checkers that are approximately square at the "equator" (polar angle theta = 90 degrees), there should be
// twice as many horizontal_checkers as vertical_checkers

class PlaneChecker: public Texture {
public:

    virtual PlaneChecker* clone() const;

    virtual RGBColor get_color(const ShadeRec& sr) const;

    void set_size(const float s);

    void set_line_width(const float w);

    void set_color1(const RGBColor& c);

    void set_color2(const RGBColor& c);

    void set_line_color(const RGBColor& c);

private:

    float       size = 1.0f;
    float       outline_width = 0.0f;
    RGBColor    color1 = RGBColor::white;
    RGBColor    color2 = RGBColor::grey;
    RGBColor    outline_color = RGBColor::black;
};

inline void PlaneChecker::set_size(const float s) {
    size = s;
}

inline void PlaneChecker::set_line_width(const float w) {
    outline_width = w;
}

inline void PlaneChecker::set_color1(const RGBColor& c) {
    color1.r = c.r; color1.g = c.g; color1.b = c.b;
}

inline void PlaneChecker::set_color2(const RGBColor& c) {
    color2.r = c.r; color2.g = c.g; color2.b = c.b;
}

inline void PlaneChecker::set_line_color(const RGBColor& c) {
    outline_color.r = c.r; outline_color.g = c.g; outline_color.b = c.b;
}

#endif