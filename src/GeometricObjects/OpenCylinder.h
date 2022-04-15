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

#ifndef __OPEN_CYLINDER__
#define __OPEN_CYLINDER__

#include "GeometricObject.h"

class OpenCylinder: public GeometricObject {
    public:

        OpenCylinder(void) = default;

        explicit OpenCylinder(double bottom, double top, double radius);

        ~OpenCylinder(void) = default;

        OpenCylinder(const OpenCylinder& oc);

        OpenCylinder(OpenCylinder&& oc) noexcept;

        OpenCylinder&
        operator= (const OpenCylinder& oc);

        OpenCylinder&
        operator= (OpenCylinder&& oc) noexcept;

        OpenCylinder*
        clone(void) const override;

        bool
        hit(const Ray& ray, double& t, ShadeRec& s) const;

    private:

        double y0           = 0.0;
        double y1           = 0.0;
        double radius       = 1.0;
        double inv_radius   = 1.0;

        static const double kEpsilon;
};

#endif
