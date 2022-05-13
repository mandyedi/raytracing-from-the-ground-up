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

#include "ViewPlane.h"

#include "../Samplers/MultiJittered.h"
#include "../Samplers/Regular.h"
#include "../Samplers/Sampler.h"

ViewPlane::~ViewPlane() {
    if (sampler_ptr) {
        delete sampler_ptr;
        sampler_ptr = nullptr;
    }
}

void ViewPlane::set_samples(const int n) {
    num_samples = n;

    if (sampler_ptr) {
        delete sampler_ptr;
        sampler_ptr = nullptr;
    }

    if (num_samples > 1) {
        sampler_ptr = new MultiJittered(num_samples);
    } else {
        sampler_ptr = new Regular(1);
    }
}

void ViewPlane::set_sampler(Sampler* sp) {
    if (sampler_ptr) {
        delete sampler_ptr;
        sampler_ptr = nullptr;
    }

    num_samples = sp->get_num_samples();
    sampler_ptr = sp;
}