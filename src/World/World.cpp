#include <fstream>

#include "World.h"
#include "Constants.h"

// geometric objects

#include "Plane.h"
#include "Sphere.h"

// tracers

#include "SingleSphere.h"
#include "MultipleObjects.h"
#include "RayCast.h"

// cameras

#include "Pinhole.h"

// lights

#include "Directional.h"

// materials

#include "Matte.h"

// utilities

#include "Vector3D.h"
#include "Point3D.h"
#include "Normal.h"
#include "ShadeRec.h"
#include "Maths.h"

// build functions

// TODO(fix): builder
// #include "BuildShadedObjects.cpp"



// tracer_ptr is set to NULL because the build functions will always construct the appropriate tracer
// ambient_ptr is set to a default ambient light because this will do for most scenes
// camera_ptr is set to NULL because the build functions will always have to construct a camera
// and set its parameters

World::World(void)
	:  	background_color(black),
		tracer_ptr(NULL),
		ambient_ptr(new Ambient),
		camera_ptr(NULL)
{}




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


// This builds a scene that consists of 35 shaded spheres and a plane.
// The objects are illuminated by a directional light and rendered with
// ambient and diffuse shading.
// Perspective viewing is used with a pinhole camera.
// Jittered sampling for antialiasing is hardwired into the PinHole::render_scene function.
// There are no sampler classes in this project.
// These are in the Chapter 5 download file.
// The spheres are the same as those in the Chapter 14 page one image. 

void
World::build_shaded_objects(void) {
	int num_samples = 1; 
	
	// view plane  

	vp.set_hres(400);
	vp.set_vres(400);
	vp.set_pixel_size(0.5);
	vp.set_samples(num_samples);
	
	// the ambient light here is the same as the default set in the World
	// constructor, and can therefore be left out
	
	Ambient* ambient_ptr = new Ambient;
	ambient_ptr->scale_radiance(1.0);
	set_ambient_light(ambient_ptr); 

	background_color = black;			// default color - this can be left out
	
	tracer_ptr = new RayCast(this); 

	
	// camera
	
	Pinhole* pinhole_ptr = new Pinhole;
	pinhole_ptr->set_eye(0, 0, 500); 
	pinhole_ptr->set_lookat(0.0);
	pinhole_ptr->set_view_distance(600.0);
	pinhole_ptr->compute_uvw();     
	set_camera(pinhole_ptr);

	
	// light
	
	Directional* light_ptr1 = new Directional;
	light_ptr1->set_direction(100, 100, 200);
	light_ptr1->scale_radiance(3.0); 	
	add_light(light_ptr1);	
	
	// Matte material reflection coefficients - common to all materials
	
	float ka = 0.25;
	float kd = 0.75;
	
	
	// spheres
	
	Matte* matte_ptr1 = new Matte;   
	matte_ptr1->set_ka(ka);	
	matte_ptr1->set_kd(kd);
	matte_ptr1->set_cd(yellow);				
	Sphere*	sphere_ptr1 = new Sphere(Point3D(5, 3, 0), 30); 
	sphere_ptr1->set_material(matte_ptr1);	   							// yellow
	add_object(sphere_ptr1);
	
	Matte* matte_ptr2 = new Matte;
	matte_ptr2->set_ka(ka);	
	matte_ptr2->set_kd(kd);
	matte_ptr2->set_cd(brown);
	Sphere*	sphere_ptr2 = new Sphere(Point3D(45, -7, -60), 20); 
	sphere_ptr2->set_material(matte_ptr2);								// brown
	add_object(sphere_ptr2);
	

	Matte* matte_ptr3 = new Matte;
	matte_ptr3->set_ka(ka);	
	matte_ptr3->set_kd(kd);
	matte_ptr3->set_cd(darkGreen);	
	Sphere*	sphere_ptr3 = new Sphere(Point3D(40, 43, -100), 17); 
	sphere_ptr3->set_material(matte_ptr3);								// dark green
	add_object(sphere_ptr3);
	
	Matte* matte_ptr4 = new Matte;
	matte_ptr4->set_ka(ka);	
	matte_ptr4->set_kd(kd);
	matte_ptr4->set_cd(orange);
	Sphere*	sphere_ptr4 = new Sphere(Point3D(-20, 28, -15), 20); 
	sphere_ptr4->set_material(matte_ptr4);								// orange
	add_object(sphere_ptr4);
	
	Matte* matte_ptr5 = new Matte;
	matte_ptr5->set_ka(ka);	
	matte_ptr5->set_kd(kd);
	matte_ptr5->set_cd(green);
	Sphere*	sphere_ptr5 = new Sphere(Point3D(-25, -7, -35), 27); 			
	sphere_ptr5->set_material(matte_ptr5);								// green
	add_object(sphere_ptr5);
	
	Matte* matte_ptr6 = new Matte;
	matte_ptr6->set_ka(ka);	
	matte_ptr6->set_kd(kd);
	matte_ptr6->set_cd(lightGreen);
	Sphere*	sphere_ptr6 = new Sphere(Point3D(20, -27, -35), 25); 
	sphere_ptr6->set_material(matte_ptr6);								// light green
	add_object(sphere_ptr6);
	
	Matte* matte_ptr7 = new Matte;
	matte_ptr7->set_ka(ka);	
	matte_ptr7->set_kd(kd);
	matte_ptr7->set_cd(green);
	Sphere*	sphere_ptr7 = new Sphere(Point3D(35, 18, -35), 22); 
	sphere_ptr7->set_material(matte_ptr7);   							// green
	add_object(sphere_ptr7);
	
	Matte* matte_ptr8 = new Matte;
	matte_ptr8->set_ka(ka);	
	matte_ptr8->set_kd(kd);
	matte_ptr8->set_cd(brown);
	Sphere*	sphere_ptr8 = new Sphere(Point3D(-57, -17, -50), 15);  
	sphere_ptr8->set_material(matte_ptr8);								// brown
	add_object(sphere_ptr8);
	
	Matte* matte_ptr9 = new Matte;
	matte_ptr9->set_ka(ka);	
	matte_ptr9->set_kd(kd);
	matte_ptr9->set_cd(lightGreen);
	Sphere*	sphere_ptr9 = new Sphere(Point3D(-47, 16, -80), 23); 
	sphere_ptr9->set_material(matte_ptr9);								// light green
	add_object(sphere_ptr9);
		
	Matte* matte_ptr10 = new Matte;
	matte_ptr10->set_ka(ka);	
	matte_ptr10->set_kd(kd);
	matte_ptr10->set_cd(darkGreen);	
	Sphere*	sphere_ptr10 = new Sphere(Point3D(-15, -32, -60), 22); 
	sphere_ptr10->set_material(matte_ptr10);     						// dark green
	add_object(sphere_ptr10);
	
	Matte* matte_ptr11 = new Matte;
	matte_ptr11->set_ka(ka);	
	matte_ptr11->set_kd(kd);
	matte_ptr11->set_cd(darkYellow);
	Sphere*	sphere_ptr11 = new Sphere(Point3D(-35, -37, -80), 22); 
	sphere_ptr11->set_material(matte_ptr11);							// dark yellow
	add_object(sphere_ptr11);
	
	Matte* matte_ptr12 = new Matte;
	matte_ptr12->set_ka(ka);	
	matte_ptr12->set_kd(kd);
	matte_ptr12->set_cd(darkYellow);
	Sphere*	sphere_ptr12 = new Sphere(Point3D(10, 43, -80), 22); 
	sphere_ptr12->set_material(matte_ptr12);							// dark yellow
	add_object(sphere_ptr12);
	
	Matte* matte_ptr13 = new Matte;
	matte_ptr13->set_ka(ka);	
	matte_ptr13->set_kd(kd);
	matte_ptr13->set_cd(darkYellow);		
	Sphere*	sphere_ptr13 = new Sphere(Point3D(30, -7, -80), 10); 
	sphere_ptr13->set_material(matte_ptr13);
	add_object(sphere_ptr13);											// dark yellow (hidden)
	
	Matte* matte_ptr14 = new Matte;
	matte_ptr14->set_ka(ka);	
	matte_ptr14->set_kd(kd);
	matte_ptr14->set_cd(darkGreen);	
	Sphere*	sphere_ptr14 = new Sphere(Point3D(-40, 48, -110), 18); 
	sphere_ptr14->set_material(matte_ptr14); 							// dark green
	add_object(sphere_ptr14);
	
	Matte* matte_ptr15 = new Matte;
	matte_ptr15->set_ka(ka);	
	matte_ptr15->set_kd(kd);
	matte_ptr15->set_cd(brown);	
	Sphere*	sphere_ptr15 = new Sphere(Point3D(-10, 53, -120), 18); 
	sphere_ptr15->set_material(matte_ptr15); 							// brown
	add_object(sphere_ptr15);
	
	Matte* matte_ptr16 = new Matte;
	matte_ptr16->set_ka(ka);	
	matte_ptr16->set_kd(kd);
	matte_ptr16->set_cd(lightPurple);
	Sphere*	sphere_ptr16 = new Sphere(Point3D(-55, -52, -100), 10); 
	sphere_ptr16->set_material(matte_ptr16);							// light purple
	add_object(sphere_ptr16);
	
	Matte* matte_ptr17 = new Matte;
	matte_ptr17->set_ka(ka);	
	matte_ptr17->set_kd(kd);
	matte_ptr17->set_cd(brown);
	Sphere*	sphere_ptr17 = new Sphere(Point3D(5, -52, -100), 15); 		
	sphere_ptr17->set_material(matte_ptr17);							// browm
	add_object(sphere_ptr17);
	
	Matte* matte_ptr18 = new Matte;
	matte_ptr18->set_ka(ka);	
	matte_ptr18->set_kd(kd);
	matte_ptr18->set_cd(darkPurple);
	Sphere*	sphere_ptr18 = new Sphere(Point3D(-20, -57, -120), 15); 
	sphere_ptr18->set_material(matte_ptr18);							// dark purple
	add_object(sphere_ptr18);
	
	Matte* matte_ptr19 = new Matte;
	matte_ptr19->set_ka(ka);	
	matte_ptr19->set_kd(kd);
	matte_ptr19->set_cd(darkGreen);
	Sphere*	sphere_ptr19 = new Sphere(Point3D(55, -27, -100), 17); 
	sphere_ptr19->set_material(matte_ptr19);							// dark green
	add_object(sphere_ptr19);

	Matte* matte_ptr20 = new Matte;
	matte_ptr20->set_ka(ka);	
	matte_ptr20->set_kd(kd);
	matte_ptr20->set_cd(brown);
	Sphere*	sphere_ptr20 = new Sphere(Point3D(50, -47, -120), 15); 
	sphere_ptr20->set_material(matte_ptr20);							// browm
	add_object(sphere_ptr20);
	 
	Matte* matte_ptr21 = new Matte;
	matte_ptr21->set_ka(ka);	
	matte_ptr21->set_kd(kd);
	matte_ptr21->set_cd(lightPurple); 	
	Sphere*	sphere_ptr21 = new Sphere(Point3D(70, -42, -150), 10); 
	sphere_ptr21->set_material(matte_ptr21);							// light purple
	add_object(sphere_ptr21);
	
	Matte* matte_ptr22 = new Matte;
	matte_ptr22->set_ka(ka);	
	matte_ptr22->set_kd(kd);
	matte_ptr22->set_cd(lightPurple);
	Sphere*	sphere_ptr22 = new Sphere(Point3D(5, 73, -130), 12); 
	sphere_ptr22->set_material(matte_ptr22);							// light purple
	add_object(sphere_ptr22);
	
	Matte* matte_ptr23 = new Matte;
	matte_ptr23->set_ka(ka);	
	matte_ptr23->set_kd(kd);
	matte_ptr23->set_cd(darkPurple);
	Sphere*	sphere_ptr23 = new Sphere(Point3D(66, 21, -130), 13); 			
	sphere_ptr23->set_material(matte_ptr23);							// dark purple
	add_object(sphere_ptr23);	
	
	Matte* matte_ptr24 = new Matte;
	matte_ptr24->set_ka(ka);	
	matte_ptr24->set_kd(kd);
	matte_ptr24->set_cd(lightPurple);  
	Sphere*	sphere_ptr24 = new Sphere(Point3D(72, -12, -140), 12); 
	sphere_ptr24->set_material(matte_ptr24);							// light purple
	add_object(sphere_ptr24);
	
	Matte* matte_ptr25 = new Matte;
	matte_ptr25->set_ka(ka);	
	matte_ptr25->set_kd(kd);
	matte_ptr25->set_cd(green);
	Sphere*	sphere_ptr25 = new Sphere(Point3D(64, 5, -160), 11); 			
	sphere_ptr25->set_material(matte_ptr25);					 		// green
	add_object(sphere_ptr25);
	  
	Matte* matte_ptr26 = new Matte;
	matte_ptr26->set_ka(ka);	
	matte_ptr26->set_kd(kd);
	matte_ptr26->set_cd(lightPurple);
	Sphere*	sphere_ptr26 = new Sphere(Point3D(55, 38, -160), 12); 		
	sphere_ptr26->set_material(matte_ptr26);							// light purple
	add_object(sphere_ptr26);
	
	Matte* matte_ptr27 = new Matte;
	matte_ptr27->set_ka(ka);	
	matte_ptr27->set_kd(kd);
	matte_ptr27->set_cd(lightPurple);
	Sphere*	sphere_ptr27 = new Sphere(Point3D(-73, -2, -160), 12); 		
	sphere_ptr27->set_material(matte_ptr27);							// light purple
	add_object(sphere_ptr27);
	 
	Matte* matte_ptr28 = new Matte;
	matte_ptr28->set_ka(ka);	
	matte_ptr28->set_kd(kd);
	matte_ptr28->set_cd(darkPurple);
	Sphere*	sphere_ptr28 = new Sphere(Point3D(30, -62, -140), 15); 
	sphere_ptr28->set_material(matte_ptr28); 							// dark purple
	add_object(sphere_ptr28);
	
	Matte* matte_ptr29 = new Matte;
	matte_ptr29->set_ka(ka);	
	matte_ptr29->set_kd(kd);
	matte_ptr29->set_cd(darkPurple);
	Sphere*	sphere_ptr29 = new Sphere(Point3D(25, 63, -140), 15); 
	sphere_ptr29->set_material(matte_ptr29);							// dark purple
	add_object(sphere_ptr29);
	
	Matte* matte_ptr30 = new Matte;
	matte_ptr30->set_ka(ka);	
	matte_ptr30->set_kd(kd);
	matte_ptr30->set_cd(darkPurple);
	Sphere*	sphere_ptr30 = new Sphere(Point3D(-60, 46, -140), 15);  
	sphere_ptr30->set_material(matte_ptr30); 							// dark purple
	add_object(sphere_ptr30);
	
	Matte* matte_ptr31 = new Matte;
	matte_ptr31->set_ka(ka);	
	matte_ptr31->set_kd(kd);
	matte_ptr31->set_cd(lightPurple);
	Sphere*	sphere_ptr31 = new Sphere(Point3D(-30, 68, -130), 12); 
	sphere_ptr31->set_material(matte_ptr31); 							// light purple
	add_object(sphere_ptr31);
	
	Matte* matte_ptr32 = new Matte;
	matte_ptr32->set_ka(ka);	
	matte_ptr32->set_kd(kd);
	matte_ptr32->set_cd(green);
	Sphere*	sphere_ptr32 = new Sphere(Point3D(58, 56, -180), 11);   
	sphere_ptr32->set_material(matte_ptr32);							//  green
	add_object(sphere_ptr32);
	
	Matte* matte_ptr33 = new Matte;
	matte_ptr33->set_ka(ka);	
	matte_ptr33->set_kd(kd);
	matte_ptr33->set_cd(green);
	Sphere*	sphere_ptr33 = new Sphere(Point3D(-63, -39, -180), 11); 
	sphere_ptr33->set_material(matte_ptr33);							// green 
	add_object(sphere_ptr33);
	
	Matte* matte_ptr34 = new Matte;
	matte_ptr34->set_ka(ka);	
	matte_ptr34->set_kd(kd);
	matte_ptr34->set_cd(lightPurple);
	Sphere*	sphere_ptr34 = new Sphere(Point3D(46, 68, -200), 10); 	
	sphere_ptr34->set_material(matte_ptr34);							// light purple
	add_object(sphere_ptr34);
	
	Matte* matte_ptr35 = new Matte;
	matte_ptr35->set_ka(ka);	
	matte_ptr35->set_kd(kd);
	matte_ptr35->set_cd(lightPurple);
	Sphere*	sphere_ptr35 = new Sphere(Point3D(-3, -72, -130), 12); 
	sphere_ptr35->set_material(matte_ptr35);							// light purple
	add_object(sphere_ptr35);
	
	
	// vertical plane
	
	Matte* matte_ptr36 = new Matte;
	matte_ptr36->set_ka(ka);	
	matte_ptr36->set_kd(kd);
	matte_ptr36->set_cd(grey);
	Plane* plane_ptr = new Plane(Point3D(0, 0, -150), Normal(0, 0, 1));
	plane_ptr->set_material(matte_ptr36);
	add_object (plane_ptr);
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
World::display_pixel(const int row, const int column, const RGBColor& raw_color) const {
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
	
	//have to start from max y coordinate to convert to screen coordinates
	int x = column;
	int y = vp.vres - row - 1;

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
	float		tmin 			= kHugeValue;
	int 		num_objects 	= objects.size();
	
	for (int j = 0; j < num_objects; j++) {
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


void
World::save_to_ppm(void) const {
	std::ofstream ofs;
	ofs.open("./image.ppm", std::ios::out | std::ios::binary);
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
	int num_objects = objects.size();
	
	for (int j = 0; j < num_objects; j++) {
		delete objects[j];
		objects[j] = NULL;
	}	
	
	objects.erase (objects.begin(), objects.end());
}


void
World::delete_lights(void) {
	int num_lights = lights.size();
	
	for (int j = 0; j < num_lights; j++) {
		delete lights[j];
		lights[j] = NULL;
	}	
	
	lights.erase (lights.begin(), lights.end());
}

