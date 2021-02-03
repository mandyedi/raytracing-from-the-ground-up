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

#include "../BRDFs/Lambertian.h"
#include "../Utilities/Constants.h"


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
Lambertian::f([[maybe_unused]] const ShadeRec& sr, [[maybe_unused]] const Vector3D& wo, [[maybe_unused]] const Vector3D& wi) const {
	return (kd * cd * invPI);
}



// this generates a direction by sampling the hemisphere with a cosine distribution
// this is called in path_shade for any material with a diffuse shading component
// the samples have to be stored with a cosine distribution

RGBColor
Lambertian::sample_f(const ShadeRec& sr, const Vector3D& wo, Vector3D& wi, float& pdf) const {

	Vector3D w(sr.normal);
	Vector3D v = Vector3D(0.0034, 1, 0.0071) ^ w;
	v.normalize();
	Vector3D u = v ^ w;

	Point3D sp = sampler_ptr->sample_hemisphere();
	wi = sp.x * u + sp.y * v + sp.z * w;
	wi.normalize();

	pdf = sr.normal * wi * invPI;

	return (kd * cd * invPI);
}


RGBColor
Lambertian::rho([[maybe_unused]] const ShadeRec& sr, [[maybe_unused]] const Vector3D& wo) const {
	return (kd * cd);
}
