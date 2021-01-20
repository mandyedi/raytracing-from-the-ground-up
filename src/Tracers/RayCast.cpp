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

#include "RayCast.h"
#include "../World/World.h"
#include "../Utilities/ShadeRec.h"
#include "../Materials/Material.h"


RayCast::RayCast(void)
	: Tracer()
{}


		
RayCast::RayCast(World* _worldPtr)
	: Tracer(_worldPtr)
{}



RayCast* 
RayCast::clone(void) const {
	return (new RayCast(*this));
}



RayCast::~RayCast(void) {}



RGBColor	
RayCast::trace_ray(const Ray& ray) const {
	ShadeRec sr(world_ptr->hit_objects(ray));
		
	if (sr.hit_an_object) {
		sr.ray = ray;			// used for specular shading
		return (sr.material_ptr->shade(sr));
	}   
	else {
		return (world_ptr->background_color);
	}
}


// this ignores the depth argument

RGBColor	
RayCast::trace_ray(const Ray& ray, [[maybe_unused]] const int depth) const {
	ShadeRec sr(world_ptr->hit_objects(ray));
		
	if (sr.hit_an_object) {
		sr.ray = ray;			// used for specular shading
		return (sr.material_ptr->shade(sr));
	}   
	else {
		return (world_ptr->background_color);
	}
}

