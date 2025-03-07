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

#include "NRooks.h"

#include "../Utilities/Random.h"

NRooks::NRooks(const int num_samples) : Sampler(num_samples) { generate_samples(); }

NRooks::NRooks(const int num_samples, const int m) : Sampler(num_samples, m) { generate_samples(); }

NRooks* NRooks::clone() const { return new NRooks(*this); }

void NRooks::generate_samples() {
    for (int p = 0; p < num_sets; p++) {
        for (int j = 0; j < num_samples; j++) {
            Point2D sp((j + rand_float()) / num_samples, (j + rand_float()) / num_samples);
            samples.push_back(sp);
        }
    }

    shuffle_x_coordinates();
    shuffle_y_coordinates();
}
