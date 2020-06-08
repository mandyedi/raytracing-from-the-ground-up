#include "Light.h"

#include "Constants.h"


Light::Light(void) {}


Light::Light(const Light& ls) {}



Light& 
Light::operator= (const Light& rhs) {
	if (this == &rhs) {
		return (*this);
	}

	return (*this);
}



Light::~Light(void) {} 



RGBColor								
Light::L(ShadeRec& s) {
	return (black);
}


