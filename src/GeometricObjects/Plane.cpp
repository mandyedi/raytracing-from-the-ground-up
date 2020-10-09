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

