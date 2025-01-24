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

#ifndef __MULTIPLE_OBJECTS__
#define __MULTIPLE_OBJECTS__

#include "Tracer.h"

class MultipleObjects : public Tracer {
public:

    MultipleObjects() = delete;

    explicit MultipleObjects(World* _world_ptr);

    ~MultipleObjects() = default;

    // For the sake of simplicity I prevent copy and move
    MultipleObjects(const MultipleObjects& mo) = delete;
    MultipleObjects(MultipleObjects&& mo) = delete;
    MultipleObjects& operator=(const MultipleObjects& mo) = delete;
    MultipleObjects& operator=(MultipleObjects&& mo) = delete;

    RGBColor trace_ray(const Ray& ray) const override;
};

#endif
