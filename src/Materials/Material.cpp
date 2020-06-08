#include "Material.h"


Material::Material(void) {}



Material::Material(const Material& m) {}




Material& 
Material::operator= (const Material& rhs) {
	if (this == &rhs) {
		return (*this);
	}

	return (*this);
}



Material::~Material(void)
{}



RGBColor
Material::shade(ShadeRec& sr) {
	return (black);
}



