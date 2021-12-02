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

#include "Emissive.h"

Emissive::Emissive (void)
	:	Material(),
		ls(1.0),
		ce(0.0)
{}




Emissive::Emissive(const Emissive& m)
	: 	Material(m),
		ls(1.0),
		ce(0.0)
{}



Material*										
Emissive::clone(void) const {
	return (new Emissive(*this));
}	



Emissive& 
Emissive::operator= (const Emissive& rhs) {
	if (this == &rhs) {
		return (*this);
	}
		
	Material::operator=(rhs);
	
	ls = rhs.ls;
    ce = rhs.ce;

	return (*this);
}



Emissive::~Emissive(void) {}



RGBColor
Emissive::area_light_shade(ShadeRec& sr) {	
	if (-sr.normal * sr.ray.d > 0.0) {
		return (ls * ce);
	}
	else {
		return (RGBColor::black);
	}
}