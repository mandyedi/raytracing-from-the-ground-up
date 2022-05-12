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

#include "SingleSphere.h"

#include "../GeometricObjects/GeometricObject.h"
#include "../Utilities/ShadeRec.h"
#include "../World/World.h"

SingleSphere::SingleSphere(World* _worldPtr) : Tracer(_worldPtr) {}

RGBColor SingleSphere::trace_ray(const Ray& ray) const {
    ShadeRec sr(*world_ptr);  // not used
    float t;                  // not used

    // This assumes that only one Sphere object is in World::objects vector.
    // TODO: add assert
    if (world_ptr->objects[0]->hit(ray, t, sr)) {
        return (RGBColor::red);
    } else {
        return (RGBColor::black);
    }
}
