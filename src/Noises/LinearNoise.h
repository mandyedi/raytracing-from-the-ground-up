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

#ifndef __LINEAR_NOISE__
#define __LINEAR_NOISE__

// using tri-linear interpolation of the lattice noise values.

#include "LatticeNoise.h"

class LinearNoise: public LatticeNoise
{
public:

    LinearNoise() = default;

    LinearNoise(int octaves, float lacunarity, float gain);

    float value_noise(const Point3D& p) const override;

    Vector3D vector_noise(const Point3D& p) const override;
};

template<class T> T
lerp(const float f, const T& a, const T& b) {
    return (a + f * (b - a));
}

#endif
