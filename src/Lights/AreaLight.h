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

#ifndef __AREA_LIGHT__
#define __AREA_LIGHT__


#include "../Utilities/RGBColor.h"
#include "../Utilities/Vector3D.h"
#include "../Utilities/Point3D.h"
#include "../Utilities/Normal.h"
#include "../Lights/Light.h"
#include "../Materials/Material.h"
#include "../GeometricObjects/GeometricObject.h"


class AreaLight: public Light {	
	public:
	
		AreaLight(void);						

		AreaLight(const AreaLight& al);				

		AreaLight* 						
		clone(void) const override;
		
		~AreaLight(void);
		
		AreaLight& 								
		operator= (const AreaLight& rhs); 
		
		void 									
		set_object(GeometricObject* obj_ptr);
		
		// From the book, chapter 18.8 The Area Light Class
		// This function will work for planar objects and objects that are defined by
		// a signle implicit function but will not work for other objects (e.g. asix-aligned box).
		Vector3D												
		get_direction(ShadeRec& s) override;
		
		RGBColor						
		L(ShadeRec& sr) override;
		
		bool									
		in_shadow(const Ray& ray, const ShadeRec& sr) const override;
		
		float
		G(const ShadeRec& sr) const override;
		
		float									
		pdf(const ShadeRec& sr) const override;
		
	private:
		
		GeometricObject* 	object_ptr;
		Material* 			material_ptr;	 // will be an emissive material
		Point3D				sample_point;
		Normal				light_normal;    // assigned in get_direction - which therefore can't be const for any light
		Vector3D			wi;			     // unit direction from hit point being shaded to sample point on light surface			
	
};


// --------------------------------------------------------------- set_object

inline void 									
AreaLight::set_object(GeometricObject* obj_ptr) {
	object_ptr = obj_ptr;
	material_ptr = object_ptr->get_material();	
}

#endif