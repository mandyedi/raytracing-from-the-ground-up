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

#include "CylindricalMap.h"
#include "../Utilities/Point3D.h"
#include "../Utilities/Constants.h"

CylindricalMap *CylindricalMap::clone() const {
    return new CylindricalMap(*this);
}

void CylindricalMap::get_texel_coordinates(const Point3D &local_hit_point, const int hres, const int vres, int &row, int &column) const {
    float phi = atan2(local_hit_point.x, local_hit_point.z);
    if (phi < 0.0f) {
        phi += TWO_PI;
    }

    float u = phi * invTWO_PI;
    float v = (local_hit_point.y + 1.0f) / 2.0f;

    column = static_cast<int>(static_cast<float>(hres - 1) * u);
    row = static_cast<int>(static_cast<float>(vres - 1) * v);
}
