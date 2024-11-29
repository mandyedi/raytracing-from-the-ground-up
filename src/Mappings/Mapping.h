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

#ifndef __MAPPING__
#define __MAPPING__

class Point3D;

class Mapping {
public:

    virtual Mapping* clone(void) const = 0;

    virtual void get_texel_coordinates(const Point3D& hit_point, const int hres, const int vres, int& row, int& column) const = 0;
};

#endif
