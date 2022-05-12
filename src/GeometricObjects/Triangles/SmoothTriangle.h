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

#ifndef __SMOOTH_TRIANGLE__
#define __SMOOTH_TRIANGLE__

// This triangle has three normals which are linearly interpolated at the hit point
// for smooth shading
// Making the normals public simplifies the code in the Grid::tessellate_smooth_sphere. This is currently
// the only function that uses this class. The only figure that uses it is Figure 23.3

#include "../../Utilities/Normal.h"
#include "../../Utilities/Point3D.h"
#include "../GeometricObject.h"

class SmoothTriangle : public GeometricObject {
public:

    Normal n0 = Normal(0.0f, 1.0f, 0.0f);  // normals at each vertex
    Normal n1 = Normal(0.0f, 1.0f, 0.0f);
    Normal n2 = Normal(0.0f, 1.0f, 0.0f);

    SmoothTriangle(void) = default;

    explicit SmoothTriangle(const Point3D& a, const Point3D& b, const Point3D& c);

    ~SmoothTriangle(void) = default;

    SmoothTriangle(const SmoothTriangle& st);

    SmoothTriangle(SmoothTriangle&& st) noexcept;

    SmoothTriangle& operator=(const SmoothTriangle& rhs);

    SmoothTriangle& operator=(SmoothTriangle&& rhs) noexcept;

    SmoothTriangle* clone(void) const override;

    BBox get_bounding_box(void);

    bool hit(const Ray& ray, float& tmin, ShadeRec& sr) const override;

    bool shadow_hit(const Ray& ray, float& tmin) const override;

private:

    Point3D v0 = Point3D(0.0f);  // vertices
    Point3D v1 = Point3D(0.0f, 0.0f, 1.0f);
    Point3D v2 = Point3D(1.0f, 0.0f, 0.0f);

    Normal interpolate_normal(const float beta, const float gamma) const;
};

#endif
