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

#include "../Utilities/RGBColor.h"
#include "BRDF.h"


BRDF::BRDF(void)
 	: sampler_ptr(nullptr)
	{}

BRDF::BRDF (const BRDF& brdf) {
	if(brdf.sampler_ptr)
		sampler_ptr	= brdf.sampler_ptr->clone();
	else  sampler_ptr = NULL;
}

BRDF&
BRDF::operator= (const BRDF& rhs) {
	if (this == &rhs) {
		return (*this);
	}

	if (sampler_ptr) {
		delete sampler_ptr;
		sampler_ptr = nullptr;
	}

	if (rhs.sampler_ptr) {
		sampler_ptr	= rhs.sampler_ptr->clone();
	}

	return (*this);
}



BRDF::~BRDF(void) {
	if (sampler_ptr) {
		delete sampler_ptr;
		sampler_ptr = nullptr;
	}
}



void
BRDF::set_sampler(Sampler* sPtr) {
	sampler_ptr = sPtr;
	sampler_ptr->map_samples_to_hemisphere(1);  // for perfect diffuse
}



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
