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

#ifndef __CONVEXPARTCYLINDER__
#define __CONVEXPARTCYLINDER__

#include "GeometricObject.h"
#include "../Utilities/BBox.h"

class ConvexPartCylinder: public GeometricObject {

public:

    ConvexPartCylinder() = default;

    ConvexPartCylinder(const double bottom, const double top, const double r, double phi1, double phi2);

    ~ConvexPartCylinder() = default;

    ConvexPartCylinder(const ConvexPartCylinder& c);

    ConvexPartCylinder(ConvexPartCylinder&& c) noexcept;

    ConvexPartCylinder&
    operator= (const ConvexPartCylinder& c);

    ConvexPartCylinder&
    operator= (ConvexPartCylinder&& c) noexcept;

    ConvexPartCylinder*
    clone() const override;

    bool
    hit(const Ray& ray, double& tmin, ShadeRec& sr) const override;

    BBox
    get_bounding_box() const override;

private:

    double y0         = -1.0;
    double y1         = 1.0;
    double radius     = 1.0;
    double inv_radius = 1.0;
    double phi_min    = 0.0;
    double phi_max    = 180.0;
};

#endif
