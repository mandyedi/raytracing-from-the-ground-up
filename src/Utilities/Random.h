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

#include <cstdlib>

inline void set_rand_seed(const int seed) { srand(seed); }

inline int rand_int() { return rand(); }

inline float rand_float() { return static_cast<float>(rand()) / static_cast<float>(RAND_MAX); }

inline float rand_float(int l, float h) { return rand_float() * (h - l) + l; }

inline int rand_int(int l, int h) { return (int)(rand_float(0, (float)h - (float)l + 1.0f) + (float)l); }