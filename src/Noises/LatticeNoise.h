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

#ifndef __LATTICE_NOISE__
#define __LATTICE_NOISE__

// This file contains the declaration of the class LatticeNoise.
// LatticeNoise is an abstract base class that defines scalar and vector
// turbulence, fractal sum, and fractional Brownian motion noise based functions.
// The scalar_noise and vector_noise functions are pure virtual.
// These are defined in the derived classes LinearNoise and CubicNoise using respectively,
// tri-linear and tri-cubic interpolation of the lattice noise values.

// The functions
//
//                value_fractal_sum
//                vector_fractal_sum
//                value_turbulence
//                value_fbm
//                vector_fbm
//
// involve sums of value_noise and vector_noise, but can be defined here in the base class because
// they are independent of the interpolation technique.
// I have not implemented a vector turbulence function.

// The three value functions: value_fractal_sum, value_turbulence, and value_fbm return values inside
// the range [0, 1].
// This simplifies the design process for textures based on the noise functions.
// As the number of octaves increases, the range of the returned values decreases because the different
// octaves don't line up. Only linear_noise potentially fills the range [0, 1]. See Chapter 31.

// When num_octaves = 1, the value functions all return value_noise,
// and the vector functions return vector_noise.

// Some of the ideas for this class came from Wilt N. (1994), Object-Oriented Ray Tracing in C++, Wiley.
// This is out of print.

// By far the biggest influence on this class is Darwyn Peachey in Ebert et al. (2003).
// The following constants and C macros are by Peachey, as is the function LatticeNoise::init_value_table
// in LatticeNoise.cpp, and the permutation_table values.

#include "../Utilities/Vector3D.h"
#include "../Utilities/Point3D.h"

const int kTableSize = 256;
const int kTableMask = kTableSize - 1;
const int seed_value = 253;

#define PERM(x)             permutation_table[(x)&kTableMask]
#define INDEX(ix,iy,iz)     PERM((ix)+PERM((iy)+PERM(iz)))
#define FLOOR(x)            ((int)(x) - ((x) < 0 && (x) != (int) (x)))

class LatticeNoise {

public:

    LatticeNoise();

    LatticeNoise(int octaves);

    LatticeNoise(int octaves, float lacunarity, float gain);

    virtual float value_noise(const Point3D& p) const = 0;
    virtual Vector3D vector_noise(const Point3D& p) const = 0;

    virtual float value_fractal_sum(const Point3D& p) const;
    virtual Vector3D vector_fractal_sum(const Point3D& p) const;

    virtual float value_turbulence(const Point3D& p) const;
    virtual float value_fbm(const Point3D& p) const;
    virtual Vector3D vector_fbm(const Point3D& p) const;

    void set_num_octaves(int octaves);
    void set_lacunarity(float lacunarity);
    void set_gain(float gain);


protected:

    int num_octaves = 1;
    float lacunarity = 2.0f;
    float gain = 0.5f;

    static const unsigned char permutation_table[kTableSize];
    float value_table[kTableSize]; // array of pseudo-random numbers
    Vector3D vector_table[kTableSize]; // array of pseudo-random unit vectors


private:

    float fbm_min;
    float fbm_max;

    void init_all(int seed);
    void init_value_table(int seed);
    void init_vector_table(int seed);
    void compute_fbm_bounds();
};

#endif
