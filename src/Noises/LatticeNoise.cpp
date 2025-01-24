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


// This file contains the definition of the class LatticeNoise

#include "LatticeNoise.h"
#include "../Utilities/Constants.h"
#include "../Utilities/Random.h"
#include "../Samplers/MultiJittered.h"

// The following table is by Darwyn Peachey in Ebert et al. (2003), page 70.

const unsigned char
LatticeNoise::permutation_table[kTableSize] =
                        {
                            225,155,210,108,175,199,221,144,203,116, 70,213, 69,158, 33,252,
                            5, 82,173,133,222,139,174, 27,  9, 71, 90,246, 75,130, 91,191,
                            169,138,  2,151,194,235, 81,  7, 25,113,228,159,205,253,134,142,
                            248, 65,224,217, 22,121,229, 63, 89,103, 96,104,156, 17,201,129,
                            36,  8,165,110,237,117,231, 56,132,211,152, 20,181,111,239,218,
                            170,163, 51,172,157, 47, 80,212,176,250, 87, 49, 99,242,136,189,
                            162,115, 44, 43,124, 94,150, 16,141,247, 32, 10,198,223,255, 72,
                            53,131, 84, 57,220,197, 58, 50,208, 11,241, 28,  3,192, 62,202,
                            18,215,153, 24, 76, 41, 15,179, 39, 46, 55,  6,128,167, 23,188,
                            106, 34,187,140,164, 73,112,182,244,195,227, 13, 35, 77,196,185,
                            26,200,226,119, 31,123,168,125,249, 68,183,230,177,135,160,180,
                            12,  1,243,148,102,166, 38,238,251, 37,240,126, 64, 74,161, 40,
                            184,149,171,178,101, 66, 29, 59,146, 61,254,107, 42, 86,154,  4,
                            236,232,120, 21,233,209, 45, 98,193,114, 78, 19,206, 14,118,127,
                            48, 79,147, 85, 30,207,219, 54, 88,234,190,122, 95, 67,143,109,
                            137,214,145, 93, 92,100,245,  0,216,186, 60, 83,105, 97,204, 52
                        };

LatticeNoise::LatticeNoise() {
    init_all(seed_value);
}

LatticeNoise::LatticeNoise(int _num_octaves)
    : num_octaves(_num_octaves) {
    init_all(seed_value);
}

LatticeNoise::LatticeNoise(int _num_octaves, float _lacunarity, float _gain)
    : num_octaves(_num_octaves),
      lacunarity(_lacunarity),
      gain(_gain) {
    init_all(seed_value);
}

void LatticeNoise::init_all(int seed) {
    init_value_table(seed_value);
    init_vector_table(seed_value);
    compute_fbm_bounds();
}

// This initialises the integer lattice of PRN's.
// It's based on valueTabInit in Peachey (2003).
void LatticeNoise::init_value_table(int seed_value) {
    set_rand_seed(seed_value);
    for (int i = 0; i < kTableSize; i++)
        value_table[i] = 1.0f - 2.0f * rand_float();   // In the range [-1, +1]
}

// init_vector_table initialises the integer lattice with pseudo-random unit vectors.
// It uses multi-jittered points on a unit sphere with a p = 0 distribution, but currently
// the multi-jittered class doesn't seed randf when it generates the samples on the unit square.

// I couldn't get the same water ripples in repeated runs in the textures demo scene when
// I used MultiJittered samples, not even when I seeded rand in MultiJittered::generate_samples.

// The problem was the setup_shuffled_indices function called in all Sampler constructors.
// This calls the standard algorithm random_shuffle, which in turn calls long_random,
// which isn't affected by the seed.
// The solution is to call a new Sampler function sample_one_set, which doesn't use the shuffled indices.
// This works fine.
// Other sampling techniques can be used in place of multi-jittered.

// The formulae for mapping points from a unit square a unit sphere are in Pharr and Humphreys pp 651-652.

void LatticeNoise::init_vector_table(int seed_value) {
    float r1, r2;
    float x, y, z;
    float r, phi;

    set_rand_seed(seed_value);
    MultiJittered* sample_ptr = new MultiJittered(256, 1); // 256 samples, 1 set

    for (int j = 0; j < kTableSize; j++) {
        Point2D sample_point = sample_ptr->sample_one_set(); // on the unit square
        r1 = sample_point.x;
        r2 = sample_point.y;
        z = 1.0f - 2.0f * r1;
        r = sqrt(1.0f - z * z);
        phi = TWO_PI * r2;
        x = r * cos(phi);
        y = r * sin(phi);
        vector_table[j] = Vector3D(x, y, z).hat(); // random unit vector
    }
}

void LatticeNoise::set_num_octaves (int _num_octaves) {
    num_octaves = _num_octaves;
    compute_fbm_bounds();
}

// we do not have to re-compute the fbm bounds because the lacunarity doesn't affect them
void LatticeNoise::set_lacunarity(float _lacunarity) {
    lacunarity = _lacunarity;
}

void LatticeNoise::set_gain(float _gain) {
    gain = _gain;
    compute_fbm_bounds();
}

void LatticeNoise::compute_fbm_bounds() {
    if (gain == 1.0f) {
        fbm_max = num_octaves;
    }
    else {
        fbm_max = (1.0f - pow(gain, num_octaves)) / (1.0f - gain);
    }

    fbm_min = -fbm_max;
}

// This has gain = 0.5f, and lacunarity = 2.0f for self-similarity
float LatticeNoise::value_fractal_sum(const Point3D& p) const {
    float amplitude = 1.0f;
    float frequency = 1.0f;
    float fractal_sum = 0.0f;

    for (int j = 0; j < num_octaves; j++) {
        fractal_sum += amplitude * value_noise(frequency * p);
        amplitude *= 0.5f;
        frequency *= 2.0f;
    }

    fractal_sum = (fractal_sum - fbm_min) / (fbm_max - fbm_min);  // map to [0, 1]

    return fractal_sum;
}

Vector3D LatticeNoise::vector_fractal_sum(const Point3D& p) const {
    float amplitude = 1.0f;
    float frequency = 1.0f;
    Vector3D sum(0.0f);

    for (int j = 0; j < num_octaves; j++) {
        sum += amplitude * vector_noise(frequency * p);
        amplitude *= 0.5f;
        frequency *= 2.0f;
    }

    return sum;
}

// min turbulence = 0.0f, max turbulence = fbm_max
float LatticeNoise::value_turbulence(const Point3D& p) const {
    float amplitude = 1.0f;
    float frequency = 1.0f;
    float turbulence = 0.0f;

    for (int j = 0 ; j < num_octaves; j++) {
        turbulence += amplitude * fabs(value_noise(frequency * p));
//        turbulence += amplitude * sqrt(fabs(value_noise(frequency * p))); // for the thin lines in Figure 30.6 (c) & (d)
        amplitude *= 0.5f;
        frequency *= 2.0f;
    }

    turbulence /= fbm_max; // map to [0, 1]

    return turbulence;
}

// this returns a value in the range [0, 1]
float LatticeNoise::value_fbm(const Point3D& p) const {
    float amplitude = 1.0f;
    float frequency = 1.0f;
    float fbm = 0.0f;

    for (int j = 0; j < num_octaves; j++) {
        fbm += amplitude * value_noise(frequency * p);
        amplitude *= gain;
        frequency *= lacunarity;
    }

    fbm = (fbm - fbm_min) / (fbm_max - fbm_min);  // map to [0, 1]

    return fbm;
}

Vector3D LatticeNoise::vector_fbm(const Point3D& p) const {
    float amplitude = 1.0f;
    float frequency = 1.0f;
    Vector3D sum(0.0f);

    for (int j = 0; j < num_octaves; j++) {
        sum += amplitude * vector_noise(frequency * p);
        amplitude *= gain;
        frequency *= lacunarity;
    }

    return (sum);
}
