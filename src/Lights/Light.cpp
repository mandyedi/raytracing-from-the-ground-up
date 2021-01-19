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

#include "Light.h"

#include "../Utilities/RGBColor.h"


Light::Light(void) {}


Light::Light([[maybe_unused]] const Light& ls) {}



Light& 
Light::operator= (const Light& rhs) {
	if (this == &rhs) {
		return (*this);
	}

	return (*this);
}



Light::~Light(void) {} 



RGBColor								
Light::L([[maybe_unused]] ShadeRec& s) {
	return (RGBColor::black);
}


