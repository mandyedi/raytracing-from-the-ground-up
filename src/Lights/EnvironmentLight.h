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

#ifndef __ENVIRONMENTLIGHT__
#define __ENVIRONMENTLIGHT__

#include "Light.h"

class Sampler;
class Material;

class EnvironmentLight: public Light {	
	public:
		
		EnvironmentLight(void);   							

		EnvironmentLight(const EnvironmentLight& dl); 
		
		Light* 									
		clone(void) const override;			

		EnvironmentLight& 									
		operator= (const EnvironmentLight& rhs); 
														
		~EnvironmentLight(void); 
	
		void 
		set_sampler(Sampler* sampler); 

		void 
		set_material(Material* material); 
	
		Vector3D												
		get_direction(ShadeRec& s);
	
		RGBColor						
		L(ShadeRec& sr);
	
		bool									
		in_shadow(const Ray& ray, const ShadeRec& sr) const;
		
		float									
		pdf(const ShadeRec& sr) const;
	
	private:
	
		Sampler*	sampler_ptr;
		Material* 	material_ptr;
		Vector3D	u, v, w;		
		Vector3D	wi;
};

#endif