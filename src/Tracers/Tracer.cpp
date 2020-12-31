#include "Tracer.h"


Tracer::Tracer(void)
	: world_ptr(nullptr)
{}



Tracer::Tracer(World* _worldPtr)
	: world_ptr(_worldPtr)
{}




Tracer::~Tracer(void) {
	if (world_ptr) {
		world_ptr = nullptr;
	}
}



RGBColor	
Tracer::trace_ray([[maybe_unused]] const Ray& ray) const {
	return (RGBColor::black);
}



RGBColor	
Tracer::trace_ray([[maybe_unused]] const Ray ray, [[maybe_unused]] const int depth) const {
	return (RGBColor::black);
}



