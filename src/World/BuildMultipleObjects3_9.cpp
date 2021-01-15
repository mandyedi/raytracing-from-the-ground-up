#include "World.h"
#include "../Utilities/RGBColor.h"
#include "../GeometricObjects/Sphere.cpp"
#include "../GeometricObjects/Plane.cpp"
#include "../Tracers/MultipleObjects.h"

void
World::build_multiple_objects_3_9(void) {
	vp.set_hres(200);
	vp.set_vres(200);
	
	background_color = RGBColor::black;
	tracer_ptr = new MultipleObjects(this);
	
	Sphere* sphere_ptr = new Sphere;
	sphere_ptr->set_center(0, -25, 0);
	sphere_ptr->set_radius(80.0);
	sphere_ptr->set_color(RGBColor::red);
	add_object(sphere_ptr);
	
	sphere_ptr = new Sphere(Point3D(0, 30, 0), 60);
	sphere_ptr->set_color(RGBColor::yellow);
	add_object(sphere_ptr);
	
	
	Plane* plane_ptr = new Plane(Point3D(0.0), Normal(0, 1, 1));
	plane_ptr->set_color(RGBColor::darkGreen);
	add_object(plane_ptr);
}

void
World::render_multiple_objects_3_9(void) {
	RGBColor	pixel_color;
	Ray			ray;
	double		zw = 100.0;
	double		x, y;

	ray.d = Vector3D(0, 0, -1);

	for ( int r = 0; r < vp.vres; r++ ) {
		for ( int c = 0; c < vp.hres; c++ ) {
			x = vp.s * (static_cast<double>(c) - 0.5 * (static_cast<double>(vp.hres) - 1.0));
			y = vp.s * (static_cast<double>(r) - 0.5 * (static_cast<double>(vp.vres) - 1.0));
			ray.o = Point3D(x, y, zw);
			pixel_color = tracer_ptr->trace_ray(ray);
			display_pixel(r, c, pixel_color);
		}
	}

	save_to_ppm();
}