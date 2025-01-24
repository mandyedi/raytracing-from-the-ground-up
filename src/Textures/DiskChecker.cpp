//  Copyright notice for changes since the originally published version:
//  Copyright (C) Eduárd Mándy 2019-2025
//  Though this C++ code was change in a large measure it still has the original copyright notice.
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.
//  See the file COPYING.txt for the full license.

#include "DiskChecker.h"

DiskChecker *DiskChecker::clone(void) const {
    return new DiskChecker(*this);
}

RGBColor DiskChecker::get_color(const ShadeRec &sr) const {
    // TODO: implemnent DiskChecker::get_color
    return RGBColor::black;
}