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

#include "Tracer.h"

#include <utility>

Tracer::Tracer(World* _worldPtr) : world_ptr(_worldPtr) {}

Tracer::~Tracer() {
    if (world_ptr) {
        world_ptr = nullptr;
    }
}

RGBColor Tracer::trace_ray([[maybe_unused]] const Ray& ray) const { return RGBColor::black; }

RGBColor Tracer::trace_ray([[maybe_unused]] const Ray& ray, [[maybe_unused]] const int depth) const { return RGBColor::black; }

RGBColor Tracer::trace_ray(const Ray ray, float& tmin, const int depth) const { return RGBColor::black; }
