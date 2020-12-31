#include "Material.h"


Material::Material(void) {}



Material::Material([[maybe_unused]] const Material& m) {}




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
Material::shade([[maybe_unused]] ShadeRec& sr) {
	return (RGBColor::black);
}



