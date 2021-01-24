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

#include <fstream>
#include <ctime>
#include <iomanip>
#include <sstream>

#include "World.h"
#include "../Utilities/Constants.h"

// geometric objects

#include "../GeometricObjects/GeometricObject.h"
#include "../GeometricObjects/Plane.h"
#include "../GeometricObjects/Sphere.h"

// tracers

#include "../Tracers/SingleSphere.h"
#include "../Tracers/MultipleObjects.h"
#include "../Tracers/RayCast.h"

// cameras

#include "../Cameras/Pinhole.h"

// lights

#include "../Lights/Directional.h"

// materials

#include "../Materials/Matte.h"

// utilities

#include "../Utilities/Vector3D.h"
#include "../Utilities/Point3D.h"
#include "../Utilities/Normal.h"
#include "../Utilities/ShadeRec.h"
#include "../Utilities/Maths.h"

// build functions

// TODO(fix): builder
// #include "BuildShadedObjects.cpp"



// tracer_ptr is set to NULL because the build functions will always construct the appropriate tracer
// ambient_ptr is set to a default ambient light because this will do for most scenes
// camera_ptr is set to NULL because the build functions will always have to construct a camera
// and set its parameters

World::World(void)
	:  	background_color(RGBColor::black),
		tracer_ptr(nullptr),
		ambient_ptr(nullptr),
		camera_ptr(nullptr)
{}

World::World(const World& w)
	: 	vp(w.vp),
		background_color(w.background_color),
		tracer_ptr(nullptr),
		ambient_ptr(nullptr),
		camera_ptr(nullptr),
		sphere(w.sphere)
{
	if (w.tracer_ptr) {
		tracer_ptr = w.tracer_ptr->clone();
	}
	else {
		tracer_ptr = nullptr;
	}

	if (w.ambient_ptr) {
		ambient_ptr = w.ambient_ptr->clone();
	}
	else {
		ambient_ptr = nullptr;
	}

	if (w.camera_ptr) {
		camera_ptr = w.camera_ptr->clone();
	}
	else {
		camera_ptr = nullptr;
	}

	for (auto object : w.objects) {
		objects.push_back(object->clone());
	}

	for (auto light : w.lights) {
		lights.push_back(light->clone());
	}

}

World&
World::operator= (const World& rhs) {
	if (this == &rhs) {
		return (*this);
	}

	vp 					= rhs.vp;
	background_color 	= rhs.background_color;
	sphere 				= rhs.sphere;

	if (tracer_ptr) {
		delete tracer_ptr;
		tracer_ptr = nullptr;
	}

	if (rhs.tracer_ptr) {
		tracer_ptr = rhs.tracer_ptr->clone();
	}

	if (ambient_ptr) {
		delete ambient_ptr;
		ambient_ptr = nullptr;
	}

	if (rhs.ambient_ptr) {
		ambient_ptr = rhs.ambient_ptr->clone();
	}

	if (camera_ptr) {
		delete camera_ptr;
		camera_ptr = nullptr;
	}

	if (rhs.camera_ptr) {
		camera_ptr = rhs.camera_ptr->clone();
	}

	for (auto object : objects) {
		delete object;
	}
	objects.clear();

	for (auto object : rhs.objects) {
		objects.push_back(object->clone());
	}

	for (auto light : lights) {
		delete light;
	}
	lights.clear();

	for (auto light : rhs.lights) {
		lights.push_back(light->clone());
	}

	return (*this);
}


World::~World(void) {	
	
	if (tracer_ptr) {
		delete tracer_ptr;
		tracer_ptr = NULL;
	}
	
		
	if (ambient_ptr) {
		delete ambient_ptr;
		ambient_ptr = NULL;
	}
			
		
	if (camera_ptr) {
		delete camera_ptr;
		camera_ptr = NULL;
	}
	
	delete_objects();	
	delete_lights();				
}


RGBColor
World::max_to_one(const RGBColor& c) const  {
	float max_value = max(c.r, max(c.g, c.b));
	
	if (max_value > 1.0) {
		return (c / max_value);
	}
	else {
		return (c);
	}
}


// Set color to red if any component is greater than one

RGBColor
World::clamp_to_color(const RGBColor& raw_color) const {
	RGBColor c(raw_color);
	
	if (raw_color.r > 1.0 || raw_color.g > 1.0 || raw_color.b > 1.0) {
		c.r = 1.0; c.g = 0.0; c.b = 0.0;
	}
		
	return (c);
}


// raw_color is the pixel color computed by the ray tracer
// its RGB floating point components can be arbitrarily large
// mapped_color has all components in the range [0, 1], but still floating point
// display color has integer components for computer display
// the Mac's components are in the range [0, 65535]
// a PC's components will probably be in the range [0, 255]
// the system-dependent code is in the function convert_to_display_color
// the function SetCPixel is a Mac OS function


void
World::display_pixel([[maybe_unused]] const int row, [[maybe_unused]] const int column, const RGBColor& raw_color) const {
	RGBColor mapped_color;

	if (vp.show_out_of_gamut) {
		mapped_color = clamp_to_color(raw_color);
	}
	else {
		mapped_color = max_to_one(raw_color);
	}

	if (vp.gamma != 1.0) {
		mapped_color = mapped_color.powc(vp.inv_gamma);
	}

	pixels.push_back((int)(mapped_color.r * 255));
	pixels.push_back((int)(mapped_color.g * 255));
	pixels.push_back((int)(mapped_color.b * 255));
}


ShadeRec									
World::hit_objects(const Ray& ray) {

	ShadeRec	sr(*this); 
	double		t;
	Normal normal;
	Point3D local_hit_point;
	double		tmin 			= static_cast<double>(kHugeValue);
	size_t 		num_objects 	= objects.size();
	
	for (size_t j = 0; j < num_objects; j++) {
		if (objects[j]->hit(ray, t, sr) && (t < tmin)) {
			sr.hit_an_object	= true;
			tmin 				= t;
			sr.material_ptr     = objects[j]->get_material();
			sr.hit_point 		= ray.o + t * ray.d;
			normal 				= sr.normal;
			local_hit_point	 	= sr.local_hit_point;
		}
	}
  
	if (sr.hit_an_object) {
		sr.t = tmin;
		sr.normal = normal;
		sr.local_hit_point = local_hit_point;
	}
		
	return(sr);   
}

ShadeRec
World::hit_bare_bones_objects(const Ray &ray) {
	ShadeRec	sr(*this);
	double		t;
	double		tmin = kHugeValue;
	size_t 		num_objects = objects.size();

	for ( size_t j = 0; j < num_objects; j++ ) {
		if ( objects[j]->hit(ray, t, sr) && (t < tmin) ) {
			sr.hit_an_object = true;
			tmin = t;
			sr.color = objects[j]->get_color();
		}
	}

	return(sr);
}

void
World::save_to_ppm(void) const {
	std::time_t t = std::time(nullptr);
	std::tm tm = *std::localtime(&t);
	std::stringstream imageFile;
	imageFile << "./image_" << std::put_time(&tm, "%Y%m%e%H%M%S") << ".ppm";

	std::ofstream ofs;
	ofs.open(imageFile.str().c_str(), std::ios::out | std::ios::binary);
	ofs << "P6\n" << vp.hres << " " << vp.vres << "\n255\n";
	for (int i : pixels) {
		ofs << static_cast<unsigned char>(i);
	}
	ofs.close();
}


// Deletes the objects in the objects array, and erases the array.
// The objects array still exists, because it's an automatic variable, but it's empty 

void
World::delete_objects(void) {
	size_t num_objects = objects.size();
	
	for ( size_t j = 0; j < num_objects; j++) {
		delete objects[j];
		objects[j] = NULL;
	}	
	
	objects.erase (objects.begin(), objects.end());
}


void
World::delete_lights(void) {
	size_t num_lights = lights.size();
	
	for (size_t j = 0; j < num_lights; j++) {
		delete lights[j];
		lights[j] = NULL;
	}	
	
	lights.erase (lights.begin(), lights.end());
}

