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

#ifndef __PATH_TRACE__
#define __PATH_TRACE__

#include "Tracer.h"

class PathTrace : public Tracer {
public:

    PathTrace() = delete;

    explicit PathTrace(World* _worldPtr);

    ~PathTrace() = default;

    // For the sake of simplicity I prevent copy and move
    PathTrace(const PathTrace& pt) = delete;
    PathTrace(PathTrace&& pt) = delete;
    PathTrace& operator=(const PathTrace& pt) = delete;
    PathTrace& operator=(PathTrace&& pt) = delete;

    RGBColor trace_ray(const Ray& ray, const int depth) const override;

    RGBColor trace_ray(const Ray ray, float& tmin, const int depth) const override;
};

#endif
