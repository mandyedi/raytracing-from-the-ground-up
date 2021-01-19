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

#include "Ray.h"


Ray::Ray (void)
	: 	o(0.0), 
		d(0.0, 0.0, 1.0) 
{}


Ray::Ray (const Point3D& origin, const Vector3D& dir)
	: 	o(origin), 
		d(dir) 
{}


Ray::Ray (const Ray& ray)
	: 	o(ray.o), 
		d(ray.d) 
{}


Ray& 
Ray::operator= (const Ray& rhs) {
	
	if (this == &rhs) {
		return (*this);
	}
		
	o = rhs.o; 
	d = rhs.d; 

	return (*this);	
}


Ray::~Ray (void) {}



