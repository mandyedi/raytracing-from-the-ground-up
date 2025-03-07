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

#ifndef __OPEN_CYLINDER__
#define __OPEN_CYLINDER__

#include "../GeometricObject.h"

class OpenCylinder : public GeometricObject {
public:

    OpenCylinder() = default;

    explicit OpenCylinder(float bottom, float top, float radius);

    ~OpenCylinder() = default;

    OpenCylinder(const OpenCylinder& oc);

    OpenCylinder(OpenCylinder&& oc) noexcept;

    OpenCylinder& operator=(const OpenCylinder& oc);

    OpenCylinder& operator=(OpenCylinder&& oc) noexcept;

    OpenCylinder* clone() const override;

    bool hit(const Ray& ray, float& t, ShadeRec& s) const;

private:

    float y0 = 0.0f;
    float y1 = 0.0f;
    float radius = 1.0f;
    float inv_radius = 1.0f;

    static const float kEpsilon;
};

#endif
