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

#ifndef __SHADE_REC__
#define __SHADE_REC__

class Material;
class World;

#include "Normal.h"
#include "Point3D.h"
#include "RGBColor.h"
#include "Ray.h"

class ShadeRec {
public:

    bool hit_an_object;
    Material* material_ptr = nullptr;  // Pointer to the nearest object's material
    Point3D hit_point;                 // World coordinates of intersection
    Point3D local_hit_point;           // World coordinates of hit point on generic object (used for texture transformations)
    Normal normal;                     // Normal at hit point
    Ray ray;
    int depth;  // recursion depth
    float t;    // ray parameter
    World& w;
    RGBColor color;

    ShadeRec() = delete;

    explicit ShadeRec(World& wr);
};

#endif