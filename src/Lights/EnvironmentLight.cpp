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

#include "EnvironmentLight.h"
#include "../Samplers/Sampler.h"
#include "../Utilities/ShadeRec.h"
#include "../Materials/Material.h"
#include "../World/World.h"

void
EnvironmentLight::set_sampler(Sampler* s_ptr) {
	if (sampler_ptr) {
		delete sampler_ptr;
		sampler_ptr = nullptr;
	}
	
	sampler_ptr = s_ptr;
	sampler_ptr->map_samples_to_hemisphere(1);
}

void
EnvironmentLight::set_material(Material* m_ptr) {
	if (material_ptr) {
		delete material_ptr;
		material_ptr = nullptr;
	}
	
	material_ptr = m_ptr;
}

Vector3D								
EnvironmentLight::get_direction(ShadeRec& sr) {
	w = sr.normal;
	v = Vector3D(0.0034, 1, 0.0071) ^ w;
	v.normalize();
	u = v ^ w;
	Point3D sp = sampler_ptr->sample_hemisphere();	
	wi = sp.x * u + sp.y * v + sp.z * w;

	return (wi);
}

RGBColor								
EnvironmentLight::L(ShadeRec& sr) {
	return (material_ptr->get_Le(sr));
}

bool									
EnvironmentLight::in_shadow(const Ray& ray, const ShadeRec& sr) const {
	float 	t;
	int 	num_objects = sr.w.objects.size();
	
	for (int j = 0; j < num_objects; j++) {
		if (sr.w.objects[j]->shadow_hit(ray, t)) {
			return true;  
		}
	}
	
	return false;  
}

// The following function is not in the book.
// It uses Equation 18.6

float									
EnvironmentLight::pdf(const ShadeRec& sr) const {
	return (sr.normal * wi * invPI);
}