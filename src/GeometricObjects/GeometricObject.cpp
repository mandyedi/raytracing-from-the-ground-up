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

#include "../Utilities/Constants.h"
#include "../Materials/Material.h"
#include "../GeometricObjects/GeometricObject.h"
#include "../Samplers/Sampler.h"



GeometricObject::~GeometricObject (void) {
	if (material_ptr != nullptr) {
		delete material_ptr;
		material_ptr = nullptr;
	}

	if (sampler_ptr != nullptr) {
		delete sampler_ptr;
		sampler_ptr = nullptr;
	}
}



GeometricObject::GeometricObject (const GeometricObject& go)
	:	color(go.color),
		shadows(go.shadows)
{
	material_ptr = go.material_ptr->clone();
	sampler_ptr = go.sampler_ptr->clone();
}



GeometricObject::GeometricObject (GeometricObject&& go) noexcept
	:	color(std::move(go.color)),
		shadows(std::exchange(go.shadows, true)),
		material_ptr(std::exchange(go.material_ptr, nullptr)),
		sampler_ptr(std::exchange(go.sampler_ptr, nullptr))
{}



GeometricObject&
GeometricObject::operator= (const GeometricObject& go) {
	color = go.color;
	shadows = go.shadows;

	if (material_ptr != nullptr) {
		delete material_ptr;
	}
	material_ptr = go.material_ptr->clone();

	if (sampler_ptr != nullptr) {
		delete sampler_ptr;
	}
	sampler_ptr = go.sampler_ptr->clone();

	return (*this);
}



GeometricObject&
GeometricObject::operator= (GeometricObject&& go) noexcept {
	color = std::move(go.color);
	shadows = std::exchange(go.shadows, true);

	if (material_ptr != nullptr) {
		delete material_ptr;
	}
	material_ptr = go.material_ptr;
	go.material_ptr = nullptr;

	if (sampler_ptr != nullptr) {
		delete sampler_ptr;
	}
	sampler_ptr = go.sampler_ptr;
	go.sampler_ptr = nullptr;

	return (*this);
}



bool
GeometricObject::shadow_hit(const Ray &ray, float &tmin) const {
    return false;
}

void
GeometricObject::set_material(Material* mPtr) {
	material_ptr = mPtr;
}

void
GeometricObject::set_sampler(Sampler* sPtr) {
	sampler_ptr = sPtr;
	sampler_ptr->map_samples_to_hemisphere(1);  // for perfect diffuse
}

BBox
GeometricObject::get_bounding_box() const {
	return BBox();
}

Point3D
GeometricObject::sample(void) {
	return Point3D();
}

Normal
GeometricObject::get_normal(const Point3D& p) {
	return Normal();
}

float
GeometricObject::pdf(const ShadeRec& sr) {
	return 0.0f;
}
