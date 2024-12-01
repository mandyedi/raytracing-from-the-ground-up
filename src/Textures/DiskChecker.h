//  Copyright notice for changes since the originally published version:
//  Copyright (C) Eduárd Mándy 2019-2021
//  Though this C++ code was change in a large measure it still has the original copyright notice.
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.
//  See the file COPYING.txt for the full license.

#ifndef __DISK_CHECKER__
#define __DISK_CHECKER__

#include "Texture.h"
#include "../Utilities/RGBColor.h"

class DiskChecker : public Texture {
public:

    virtual DiskChecker *clone() const;

    virtual RGBColor get_color(const ShadeRec &sr) const;

    void set_num_horizontal_checkers(const int num_horizontal);

    void set_num_vertical_checkers(const int num_vertical);

    void set_horizontal_line_width(const float w);

    void set_vertical_line_width(const float w);

    void set_color1(const RGBColor &c);

    void set_color2(const RGBColor &c);

    void set_line_color(const RGBColor &c);

private:

    int         num_horizontal_checkers = 20;
    int         num_vertical_checkers = 10;
    float       horizontal_line_width = 0.0f;    // width of the horizontal lines as a fraction of the checker width
    float       vertical_line_width = 0.0f;      // width of the vertical lines as a fraction of the checker width
    RGBColor    color1 = RGBColor::white;
    RGBColor    color2 = RGBColor::grey;
    RGBColor    line_color = RGBColor::black;
};

inline void DiskChecker::set_num_horizontal_checkers(const int num_horizontal) {
    num_horizontal_checkers = num_horizontal;
}

inline void DiskChecker::set_num_vertical_checkers(const int num_vertical) {
    num_vertical_checkers = num_vertical;
}

inline void DiskChecker::set_horizontal_line_width(const float w) {
    horizontal_line_width = w;
}

inline void DiskChecker::set_vertical_line_width(const float w) {
    vertical_line_width = w;
}

inline void DiskChecker::set_color1(const RGBColor &c) {
    color1.r = c.r; color1.g = c.g; color1.b = c.b;
}

inline void DiskChecker::set_color2(const RGBColor &c) {
    color2.r = c.r; color2.g = c.g; color2.b = c.b;
}

inline void DiskChecker::set_line_color(const RGBColor &c) {
    line_color.r = c.r; line_color.g = c.g; line_color.b = c.b;
}

#endif