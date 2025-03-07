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

#include "Regular.h"

Regular::Regular(const int num) : Sampler(num) { generate_samples(); }

Regular* Regular::clone() const { return new Regular(*this); }

void Regular::generate_samples() {
    int n = (int)sqrt((float)num_samples);

    for (int j = 0; j < num_sets; j++) {
        for (int p = 0; p < n; p++) {
            for (int q = 0; q < n; q++) {
                samples.push_back(Point2D(((float)q + 0.5f) / (float)n, ((float)p + 0.5f) / (float)n));
            }
        }
    }
}
