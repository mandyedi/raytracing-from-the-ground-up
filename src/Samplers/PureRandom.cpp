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

#include "PureRandom.h"

#include "../Utilities/Random.h"

PureRandom::PureRandom(const int num) : Sampler(num) { generate_samples(); }

PureRandom* PureRandom::clone() const { return new PureRandom(*this); }

void PureRandom::generate_samples() {
    for (int p = 0; p < num_sets; p++) {
        for (int q = 0; q < num_samples; q++) {
            samples.push_back(Point2D(rand_float(), rand_float()));
        }
    }
}
