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

#include "AmbientOccluder.h"
#include "../Samplers/Sampler.h"


AmbientOccluder::AmbientOccluder(void)
	: Light(),
      ls(1.0),
      color(1.0),
      min_amount(0.0),
      u(1.0, 0.0, 0.0),
      v(0.0, 1.0, 0.0),
      w(0.0, 0.0, 1.0),
      sampler_ptr(nullptr)
{}



AmbientOccluder::AmbientOccluder(const AmbientOccluder& other)
	: 	Light(other),
		ls(other.ls),
		color(other.color),
		min_amount(other.min_amount),
		u(other.u),
		v(other.v),
		w(other.w)
{
	if (other.sampler_ptr) {
		sampler_ptr = other.sampler_ptr->clone();
	}
	else {
		sampler_ptr = nullptr;
	}
}



Light*
AmbientOccluder::clone(void) const {
	return (new AmbientOccluder(*this));
}



AmbientOccluder&
AmbientOccluder::operator= (const AmbientOccluder& other)
{
	if (this == &other) {
		return *this;
	}

	Light::operator=(other);

	ls		= other.ls;
	color 	= other.color;
	u 		= other.u;
	v 		= other.v;
	w 		= other.w;

	return *this;
}



AmbientOccluder::~AmbientOccluder(void) {
	if (sampler_ptr) {
		delete sampler_ptr;
		sampler_ptr = nullptr;
	}
}


void
AmbientOccluder::set_sampler(Sampler* s_ptr) {
	if (sampler_ptr) {
		delete sampler_ptr;
		sampler_ptr = nullptr;
	}
	
	sampler_ptr = s_ptr;
	sampler_ptr->map_samples_to_hemisphere(1);
}

Vector3D
AmbientOccluder::get_direction(ShadeRec& sr) {
	Point3D sp = sampler_ptr->sample_hemisphere();
	return (sp.x * u + sp.y * v + sp.z * w);
}

bool									
AmbientOccluder::in_shadow(const Ray& ray, const ShadeRec& sr) const {			
	float 	t;
	int 	num_objects = sr.w.objects.size();
	
	for (int j = 0; j < num_objects; j++) {
		if (sr.w.objects[j]->shadow_hit(ray, t)) {
			return true;  
		}
	}
	
	return false;  
}

RGBColor
AmbientOccluder::L(ShadeRec& sr) {	
	w = sr.normal;	
	v = w ^ Vector3D(0.0072, 1.0, 0.0034); // jitter the up vector in case normal is vertical
	v.normalize();
	u = v ^ w;
	
	Ray shadow_ray;
	shadow_ray.o = sr.hit_point;
	shadow_ray.d = get_direction(sr);  
	
	if (in_shadow(shadow_ray, sr)) {
		return (min_amount * ls * color);
	}
	else {
		return (ls * color);
	}
}