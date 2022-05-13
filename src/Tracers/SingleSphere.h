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

#ifndef __SINGLE_SPHERE__
#define __SINGLE_SPHERE__

#include "Tracer.h"

class SingleSphere : public Tracer {
public:

    SingleSphere() = delete;

    explicit SingleSphere(World* _worldPtr);

    ~SingleSphere() = default;

    // For the sake of simplicity I prevent copy and move
    SingleSphere(const SingleSphere& ss) = delete;
    SingleSphere(SingleSphere&& ss) = delete;
    SingleSphere& operator=(const SingleSphere& ss) = delete;
    SingleSphere& operator=(SingleSphere&& ss) = delete;

    RGBColor trace_ray(const Ray& ray) const override;
};

#endif
