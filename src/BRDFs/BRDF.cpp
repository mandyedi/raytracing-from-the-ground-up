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

#include "../Utilities/RGBColor.h"
#include "BRDF.h"


BRDF::BRDF(void) {}


BRDF::BRDF([[maybe_unused]]const BRDF& brdf) {}	




BRDF&														
BRDF::operator= (const BRDF& rhs) {
	if (this == &rhs)
		return (*this);

	return (*this);
}



BRDF::~BRDF(void) {}  



RGBColor
BRDF::f([[maybe_unused]] const ShadeRec& sr, [[maybe_unused]] const Vector3D& wo, [[maybe_unused]] const Vector3D& wi) const {
	return (RGBColor::black);
}



RGBColor
BRDF::sample_f([[maybe_unused]] const ShadeRec& sr, [[maybe_unused]] const Vector3D& wo, [[maybe_unused]] Vector3D& wi) const {
	return (RGBColor::black);
}



RGBColor
BRDF::sample_f([[maybe_unused]] const ShadeRec& sr, [[maybe_unused]] const Vector3D& wo, [[maybe_unused]] Vector3D& wi, [[maybe_unused]] float& pdf) const {
	return (RGBColor::black);
}


	
RGBColor
BRDF::rho([[maybe_unused]] const ShadeRec& sr, [[maybe_unused]] const Vector3D& wo) const {
	return (RGBColor::black);
}

