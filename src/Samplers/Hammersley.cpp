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

#include "Hammersley.h"
#include "../Utilities/Maths.h"




Hammersley::Hammersley(const int num)
    :   Sampler(num) {
    generate_samples();
}



Hammersley*
Hammersley::clone(void) const {
    return (new Hammersley(*this));
}




float
Hammersley::phi(int j) {
    float x = 0.0f;
    float f = 0.5f;

    while (j) {
        x += f * (float) (j % 2);
        j /= 2;
        f *= 0.5;
    }

    return (x);
}




void
Hammersley::generate_samples(void) {
    for (int p = 0; p < num_sets; p++) {
        for (int j = 0; j < num_samples; j++) {
            Point2D pv((float) j / (float) num_samples, (float) phi(j));
            samples.push_back(pv);
        }
    }
}


