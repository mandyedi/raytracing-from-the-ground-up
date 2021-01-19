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

#include "MultipleObjects.h"
#include "../World/World.h"


MultipleObjects::MultipleObjects(void)
	: Tracer()
{}


		
MultipleObjects::MultipleObjects(World* _worldPtr)
	: Tracer(_worldPtr)
{}



MultipleObjects::~MultipleObjects(void) {}



RGBColor	
MultipleObjects::trace_ray(const Ray& ray) const {
	ShadeRec sr(world_ptr->hit_bare_bones_objects(ray));
		
	if (sr.hit_an_object) {
		return (sr.color);
	}  
	else {
		return (world_ptr->background_color);
	}
}

