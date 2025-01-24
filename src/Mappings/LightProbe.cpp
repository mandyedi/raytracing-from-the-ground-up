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

#include <cmath>

#include "LightProbe.h"
#include "../Utilities/Point3D.h"
#include "../Utilities/Constants.h"

LightProbe *LightProbe::clone() const {
    return new LightProbe(*this);
}

void LightProbe::get_texel_coordinates(const Point3D &local_hit_point, const int hres, const int vres, int &row, int &column) const {
    float x = local_hit_point.x;
    float y = local_hit_point.y;
    float z = local_hit_point.z;

    float d = sqrt(x * x + y * y);
    float sin_beta = y / d;
    float cos_beta = x / d;
    float alpha;

    if (map_type == MapType::LightProbe) {
        alpha = acos(z);
    }

    if (map_type == MapType::Panoramic) {
        alpha = acos(-z);
    }

    float r = alpha * invPI;
    float u = (1.0f + r * cos_beta) * 0.5f;
    float v = (1.0f + r * sin_beta) * 0.5f;
    column = static_cast<int>(static_cast<float>(hres - 1) * u);
    row = static_cast<int>(static_cast<float>(vres - 1) * v);
}
