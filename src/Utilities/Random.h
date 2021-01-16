//  Copyright (C) Kevin Suffern 2000-2007.
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.
//  See the file COPYING.txt for the full license.

//  Copyright notices for changes since the originally published version:
//  Copyright (C) Eduárd Mándy 2019-2021
//  Though this C++ code was change in a large measure it still has the original copyright notices.
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.
//  See the file COPYING.txt for the full license.

#include <cstdlib>

inline void
set_rand_seed(const int seed) {
	srand(seed);
}

inline int
rand_int(void) {
	return (rand());
}

inline float
rand_float(void) {
	return (static_cast<float>(rand()) / static_cast<float>(RAND_MAX));
}