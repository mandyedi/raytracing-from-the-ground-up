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

#include "CompoundSolidCylinder.h"
#include "OpenCylinder.h"
#include "Disk.h"

CompoundSolidCylinder::CompoundSolidCylinder()
    : Compound()
{
    objects.push_back(new Disk(	Point3D(0.0f, 0.0f, 0.0f), Normal(0.0f, -1.0f, 0.0f), 1.0f));
    objects.push_back(new Disk(	Point3D(0.0f, 1.0f, 0.0f), Normal(0.0f, 1.0f, 0.0f), 1.0f));
    OpenCylinder *openCylinder = new OpenCylinder(0.0f, 1.0f, 1.0f);
    objects.push_back(openCylinder);
    bbox = openCylinder->get_bounding_box();
}


CompoundSolidCylinder::CompoundSolidCylinder(const float bottom, const float top, const float radius)
    : Compound()
{
    objects.push_back(new Disk(	Point3D(0, bottom, 0),
                                Normal(0, -1, 0),
                                radius));

    objects.push_back(new Disk(	Point3D(0, top, 0),
                                Normal(0, 1, 0),
                                radius));

    OpenCylinder *openCylinder = new OpenCylinder(bottom, top, radius);
    objects.push_back(openCylinder);
    bbox = openCylinder->get_bounding_box();
}

CompoundSolidCylinder::CompoundSolidCylinder(const CompoundSolidCylinder& sc)
    : Compound(sc),
      bbox(sc.bbox)
{}

CompoundSolidCylinder::CompoundSolidCylinder(CompoundSolidCylinder&& sc) noexcept
    : Compound(std::move(sc)),
      bbox(std::move(sc.bbox))
{}

CompoundSolidCylinder::~CompoundSolidCylinder() {}

CompoundSolidCylinder&
CompoundSolidCylinder::operator= (const CompoundSolidCylinder& sc)
{
    Compound::operator= (sc);
    bbox = sc.bbox;
    return *this;
}

CompoundSolidCylinder&
CompoundSolidCylinder::operator= (CompoundSolidCylinder&& sc) noexcept
{
    Compound::operator= (std::move(sc));
    bbox = std::move(sc.bbox);
    return *this;
}

CompoundSolidCylinder*
CompoundSolidCylinder::clone() const
{
    return (new CompoundSolidCylinder(*this));
}

bool
CompoundSolidCylinder::hit(const Ray& ray, float& tmin, ShadeRec& sr) const {
    if (bbox.hit(ray)) {
        return (Compound::hit(ray, tmin, sr));
    }
    else {
        return false;
    }
}

bool
CompoundSolidCylinder::shadow_hit(const Ray &ray, float &tmin) const {
    if (bbox.hit(ray)) {
        return Compound::shadow_hit(ray, tmin);
    }
    else {
        return false;
    }
}
