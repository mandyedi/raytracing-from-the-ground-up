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

#include "../Materials/Material.h"


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



