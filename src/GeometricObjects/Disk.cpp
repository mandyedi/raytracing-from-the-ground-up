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

#include <utility>
#include "Disk.h"

const double Disk::kEpsilon = 0.001;



Disk::Disk(const Point3D& p, const Normal& n, float r)
    : GeometricObject(),
      center(p),
      normal(n),
      r_squared(r * r)
{}



Disk::Disk (const Disk& d)
	:	GeometricObject(d),
		center(d.center),
		normal(d.normal),
		r_squared(d.r_squared)
{}



Disk::Disk (Disk&& d) noexcept
	:	GeometricObject(std::move(d)),
		center(std::move(d.center)),
		normal(std::move(d.normal)),
		r_squared(std::exchange(d.r_squared, 1.0))
{}



Disk&
Disk::operator= (const Disk& d) {
	GeometricObject::operator=(d);

	center				= d.center;
	normal				= d.normal;
	r_squared			= d.r_squared;

	return (*this);
}



Disk&
Disk::operator= (Disk&& d) noexcept {
	GeometricObject::operator=(std::move(d));

	center				= std::move(d.center);
	normal				= std::move(d.normal);
	r_squared			= std::exchange(d.r_squared, 1.0);

	return (*this);
}



Disk*
Disk::clone(void) const {
	return (new Disk(*this));
}



bool
Disk::hit(const Ray& ray, double& tmin, ShadeRec& sr) const {
	double t = (center - ray.o) * normal / (ray.d * normal);

	if (t <= kEpsilon) {
		return (false);
	}

	Point3D p = ray.o + t * ray.d;

	if (center.d_squared(p) < r_squared) {
		tmin 				= t;
		sr.normal 			= normal;
		sr.local_hit_point	= p;
		return (true);
	}
	else {
		return (false);
	}
}
