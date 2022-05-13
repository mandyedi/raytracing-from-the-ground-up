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

#ifndef __GLOBAL_TRACE__
#define __GLOBAL_TRACE__

#include "Tracer.h"

class GlobalTrace : public Tracer {
public:

    GlobalTrace() = delete;

    explicit GlobalTrace(World* _worldPtr);

    ~GlobalTrace() = default;

    // For the sake of simplicity I prevent copy and move
    GlobalTrace(const GlobalTrace& pt) = delete;
    GlobalTrace(GlobalTrace&& pt) = delete;
    GlobalTrace& operator=(const GlobalTrace& pt) = delete;
    GlobalTrace& operator=(GlobalTrace&& pt) = delete;

    RGBColor trace_ray(const Ray& ray, int depth) const override;

    RGBColor trace_ray(const Ray ray, float& tmin, const int depth) const override;
};

#endif
