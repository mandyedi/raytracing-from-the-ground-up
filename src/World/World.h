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

#ifndef __WORLD__
#define __WORLD__


// The World class does not have a copy constructor or an assignment operator, for the followign reasons:

// 1 	There's no need to copy construct or assign the World
// 2 	We wouldn't want to do this anyway, because the world can contain an arbitray amount of data
// 3 	These operations wouldn't work because the world is self-referencing:
//	 	the Tracer base class contains a pointer to the world. If we wrote a correct copy constructor for the 
// 	  	Tracer class, the World copy construtor would call itself recursively until we ran out of memory. 


#include <vector>

#include "ViewPlane.h"
#include "../Utilities/RGBColor.h"
#include "../Tracers/Tracer.h"
#include "../GeometricObjects/GeometricObject.h"
#include "../GeometricObjects/Sphere.h"
#include "../Utilities/Ray.h"
#include "../Tracers/SingleSphere.h"

#include "../Cameras/Camera.h"
#include "../Lights/Light.h"
#include "../Lights/Ambient.h"

using namespace std;

class World {	
	public:
	
		ViewPlane					vp;
		RGBColor					background_color;
		Tracer*						tracer_ptr;
		Light*   					ambient_ptr;
		Camera*						camera_ptr;		
		Sphere 						sphere;		// for Chapter 3 only
		vector<GeometricObject*>	objects;		
		vector<Light*> 				lights;			

	public:
	
		World(void);												
		
		~World();
								
		void 
		add_object(GeometricObject* object_ptr);
		
		void 
		add_light(Light* light_ptr); 
		
		void
		set_ambient_light(Light* light_ptr);			
		
		void
		set_camera(Camera* c_ptr);	 
						
		RGBColor
		max_to_one(const RGBColor& c) const;
		
		RGBColor
		clamp_to_color(const RGBColor& c) const;
		
		void
		display_pixel(const int row, const int column, const RGBColor& pixel_color) const;

		ShadeRec
		hit_objects(const Ray& ray);

		ShadeRec
		hit_bare_bones_objects(const Ray &ray);
		
		void
		save_to_ppm(void) const;

	private:
		
		mutable std::vector<int> pixels;

		void 
		delete_objects(void);
		
		void 
		delete_lights(void);

	public:
		// The following methods are example codes from book chapters
		// These are not necessary to use the ray tracer engine

		void
		build_shaded_objects(void);

		void
		World::build_single_sphere_3_6_5(void);

		void
		World::build_multiple_objects_3_9(void);

		void
		World::render_single_sphere_3_6_5( void );

		void
		World::render_multiple_objects_3_9(void);
};



inline void 
World::add_object(GeometricObject* object_ptr) {  
	objects.push_back(object_ptr);	
}



inline void 
World::add_light(Light* light_ptr) {  
	lights.push_back(light_ptr);
}



inline void
World::set_ambient_light(Light* light_ptr) {
	ambient_ptr = light_ptr;
}



inline void
World::set_camera(Camera* c_ptr) {
	camera_ptr = c_ptr;
}

#endif
