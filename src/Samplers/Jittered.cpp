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

#include "Jittered.h"

#include "../Utilities/Random.h"

Jittered::Jittered(const int num_samples) : Sampler(num_samples) { generate_samples(); }

Jittered::Jittered(const int num_samples, const int m) : Sampler(num_samples, m) { generate_samples(); }

Jittered* Jittered::clone(void) const { return (new Jittered(*this)); }

void Jittered::generate_samples(void) {
    int n = (int)sqrt((float)num_samples);

    for (int p = 0; p < num_sets; p++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                Point2D sp((k + rand_float()) / n, (j + rand_float()) / n);
                samples.push_back(sp);
            }
        }
    }
}
