//  Copyright (C) Kevin Suffern 2000-2007.
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.
//  See the file COPYING.txt for the full license.

//  Copyright notice for changes since the originally published version:
//  Copyright (C) Eduárd Mándy 2019-2021
//  Though this C++ code was change in a large measure it still has the original copyright notice.
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.
//  See the file COPYING.txt for the full license.

#include <cmath>

#include "PlaneChecker.h"
#include "../Utilities/Constants.h"

PlaneChecker* PlaneChecker::clone(void) const {
    return new PlaneChecker(*this);
}

RGBColor PlaneChecker::get_color(const ShadeRec & sr) const {
    float x = sr.local_hit_point.x;
    float z = sr.local_hit_point.z;
    float ix = floor(x / size);
    float iz = floor(z / size);
    float fx = x / size - ix;
    float fz = z / size - iz;
    float width = 0.5f * outline_width / size;
    bool in_outline = (fx < width || fx > 1.0 - width) || (fz < width || fz > 1.0 - width);

    if ((static_cast<int>(ix) + static_cast<int>(iz)) % 2 == 0) {
        if (!in_outline) {
            return (color1);
        }
    }
    else {
        if (!in_outline) {
            return (color2);
        }
    }

    return outline_color;
}
