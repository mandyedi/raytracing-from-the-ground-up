#include "Lambertian.h"
#include "Constants.h"


Lambertian::Lambertian(void) 
	:   BRDF(),
		kd(0.0), 
		cd(0.0)
{}



Lambertian::Lambertian(const Lambertian& lamb) 
	:   BRDF(lamb),
		kd(lamb.kd), 
		cd(lamb.cd)
{}



Lambertian* 
Lambertian::clone(void) const {
	return (new Lambertian(*this));
}	



Lambertian::~Lambertian(void) {}



Lambertian& 
Lambertian::operator= (const Lambertian& rhs) {
	if (this == &rhs) {
		return (*this);
	}
		
	BRDF::operator= (rhs);
	
	kd = rhs.kd; 
	cd = rhs.cd;
	
	return (*this);
}



RGBColor
Lambertian::f(const ShadeRec& sr, const Vector3D& wo, const Vector3D& wi) const {
	return (kd * cd * invPI);
}



RGBColor
Lambertian::rho(const ShadeRec& sr, const Vector3D& wo) const {
	return (kd * cd);
}


