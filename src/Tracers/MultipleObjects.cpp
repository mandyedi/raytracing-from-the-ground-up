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

