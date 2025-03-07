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

// This is the declaration of the base class Tracer
// The tracer classes have no copy constructor, assignment operator. or clone function because
// of the world pointer, which should not be assigned or copy constructed
// See comments in the World.h file.

#ifndef __TRACER__
#define __TRACER__

#include "../Utilities/Constants.h"
#include "../Utilities/RGBColor.h"
#include "../Utilities/Ray.h"

class World;

class Tracer {
public:

    Tracer() = delete;

    explicit Tracer(World* _world_ptr);

    virtual ~Tracer();

    // For the sake of simplicity I prevent copy and move
    Tracer(const Tracer& t) = delete;
    Tracer(Tracer&& t) = delete;
    Tracer& operator=(const Tracer& t) = delete;
    Tracer& operator=(Tracer&& t) = delete;

    // TODO: review usage of tracer functions, remove unused
    virtual RGBColor trace_ray(const Ray& ray) const;

    virtual RGBColor trace_ray(const Ray& ray, const int depth) const;

    virtual RGBColor trace_ray(const Ray ray, float& tmin, const int depth) const;

protected:

    World* world_ptr;
};

#endif
