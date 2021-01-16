//  Copyright (C) Kevin Suffern 2000-2007.
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.
//  See the file COPYING.txt for the full license.

//  Copyright notices for changes since the originally published version:
//  Copyright (C) Eduárd Mándy 2019-2021
//  Though this C++ code was change in a large measure it still has the original copyright notices.
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.
//  See the file COPYING.txt for the full license.

#include "Plane.h"

const double Plane::kEpsilon = 0.001;


Plane::Plane(void)	
	: 	GeometricObject(),
		a(0.0),
		n(0, 1, 0)						
{}



Plane::Plane(const Point3D& point, const Normal& normal)
	:	GeometricObject(),
		a(point),
		n(normal)
{
		n.normalize();
}



Plane::Plane(const Plane& plane) 
	:	GeometricObject(plane),
		a(plane.a),
		n(plane.n) 				
{}



Plane* 
Plane::clone(void) const {
	return (new Plane(*this));
}



Plane& 
Plane::operator= (const Plane& rhs)	{
	
	if (this == &rhs) {
		return (*this);
	}

	GeometricObject::operator= (rhs);

	a = rhs.a;
	n = rhs.n;

	return (*this);
}



Plane::~Plane(void)				
{}



bool 															 
Plane::hit(const Ray& ray, double& tmin, ShadeRec& sr) const {	
	double t = (a - ray.o) * n / (ray.d * n); 
														
	if (t > kEpsilon) {
		tmin = t;
		sr.normal = n;
		sr.local_hit_point = ray.o + t * ray.d;
		
		return (true);	
	}

	return(false);
}

