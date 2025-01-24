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

#ifndef __IMAGE__
#define __IMAGE__

#include <vector>
#include "RGBColor.h"

class Image {
public:

    void read_ppm_file(const char *file_name);

    int get_hres();

    int get_vres();

    RGBColor get_color(const int row, const int col) const;

private:
    int hres = 0;
    int vres = 0;
    std::vector<RGBColor> pixels;
};

inline int Image::get_hres() {
    return hres;
}

inline int Image::get_vres() {
    return vres;
}

#endif
