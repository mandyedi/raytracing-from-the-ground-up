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

#ifndef __SPHERE_CHECKER__
#define __SPHERE_CHECKER__

#include "Texture.h"
#include "../Utilities/RGBColor.h"

// For checkers that are approximately square at the "equator" (polar angle theta = 90 degrees), there should be
// twice as many horizontal_checkers as vertical_checkers

class SphereChecker: public Texture {
public:

    virtual SphereChecker* clone() const;

    virtual RGBColor get_color(const ShadeRec& sr) const;

    void set_num_horizontal_checkers(const int num_horizontal);

    void set_num_vertical_checkers(const int num_vertical);

    void set_horizontal_line_width(const float w);

    void set_vertical_line_width(const float w);

    void set_color1(const RGBColor& c);

    void set_color2(const RGBColor& c);

    void set_line_color(const RGBColor& c);

private:

    int         num_horizontal_checkers = 20;
    int         num_vertical_checkers = 10;
    float       horizontal_line_width = 0.0f;    // width of the horizontal lines as a fraction of the checker width
    float       vertical_line_width = 0.0f;      // width of the vertical lines as a fraction of the checker width
    RGBColor    color1 = RGBColor::white;
    RGBColor    color2 = RGBColor::grey;
    RGBColor    line_color = RGBColor::black;
};

inline void SphereChecker::set_num_horizontal_checkers(const int num_horizontal) {
    num_horizontal_checkers = num_horizontal;
}

inline void SphereChecker::set_num_vertical_checkers(const int num_vertical) {
    num_vertical_checkers = num_vertical;
}

inline void SphereChecker::set_horizontal_line_width(const float w) {
    horizontal_line_width = w;
}

inline void SphereChecker::set_vertical_line_width(const float w) {
    vertical_line_width = w;
}

inline void SphereChecker::set_color1(const RGBColor& c) {
color1.r = c.r; color1.g = c.g; color1.b = c.b;
}

inline void SphereChecker::set_color2(const RGBColor& c) {
color2.r = c.r; color2.g = c.g; color2.b = c.b;
}

inline void SphereChecker::set_line_color(const RGBColor& c) {
    line_color.r = c.r; line_color.g = c.g; line_color.b = c.b;
}

#endif