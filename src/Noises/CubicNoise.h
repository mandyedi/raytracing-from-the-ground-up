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

#ifndef __CUBIC_NOISE__
#define __CUBIC_NOISE__

// This file contains the declaration of the class CubicNoise.
// CubicNoise defines the functions scalar_noise and vector_noise
// using tri-cubic interpolation of the lattice noise values.

#include "LatticeNoise.h"
#include "../Utilities/Vector3D.h"

class CubicNoise: public LatticeNoise {
public:

    CubicNoise() = default;

    CubicNoise(int octaves);

    CubicNoise(int octaves, float lacunarity, float gain);

    float value_noise(const Point3D& p) const override;

    Vector3D vector_noise(const Point3D& p) const override;
};

// Cubic interpolation using a Catmull-Rom four knot spline.
// This is templated so that we can use it to interpolate floats and Vector3Ds.
// This is not a class member function.

template<class T> T
four_knot_spline(const float x, const T knots[]) {
    T c3 = -0.5f * knots[0] + 1.5f * knots[1] - 1.5f * knots[2] + 0.5f * knots[3];
    T c2 = knots[0] - 2.5f * knots[1] + 2.0f * knots[2] - 0.5f * knots[3];
    T c1 = 0.5f * (-knots[0] + knots [2]);
    T c0 = knots[1];

    return T((c3 * x + c2) * x + c1) * x + c0;
}

#endif
