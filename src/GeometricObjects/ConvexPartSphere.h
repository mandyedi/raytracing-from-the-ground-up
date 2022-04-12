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

#ifndef __CONVEXPARTSPHERE__
#define __CONVEXPARTSPHERE__

#include "GeometricObject.h"
#include "../Utilities/Constants.h"

class ConvexPartSphere: public GeometricObject {

public:

    ConvexPartSphere() = default;

    ConvexPartSphere(	const Point3D 	c,
                        const double 	r,
                        const double 	azimuth_min,	// in degrees
                        const double 	azimuth_max,	// in degrees
                        const double 	polar_min,		// in degrees measured from top
                        const double 	polar_max);		// in degrees measured from top

    ConvexPartSphere(const Point3D c, const double radius);

    ~ConvexPartSphere() = default;

    ConvexPartSphere(const ConvexPartSphere& c);

    ConvexPartSphere(ConvexPartSphere&& c) noexcept;

    ConvexPartSphere&
    operator= (const ConvexPartSphere& c);

    ConvexPartSphere&
    operator= (ConvexPartSphere&& c) noexcept;

    ConvexPartSphere*
    clone() const override;

    bool
    hit(const Ray& ray, double& tmin, ShadeRec& sr) const override;

private:

    Point3D center        = Point3D(0.0);
    double  radius        = 1.0;
    double  phi_min       = 0.0;
    double  phi_max       = TWO_PI;
    double  theta_min     = 0.0;             // measured from top
    double  theta_max     = PI;              // measured from top
    double  cos_theta_min = 1.0;
    double  cos_theta_max = -1.0;
};

#endif
