//  Copyright (C) Kevin Suffern 2000-2007.
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.
//  See the file COPYING.txt for the full license.

//  Copyright notices for changes since the originally published version:
//  Copyright (C) Eduárd Mándy 2019-2021
//  Though this C++ code was change in a large measure it still has the original copyright notices.
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.
//  See the file COPYING.txt for the full license.

#ifndef __DIRECTIONAL__
#define __DIRECTIONAL__

#include "Light.h"
#include "../Utilities/Vector3D.h"
#include "../Utilities/RGBColor.h"

#include "../World/World.h"			// you will need this later on for shadows
#include "../Utilities/ShadeRec.h"


class Directional: public Light {
	public:
	
		Directional(void);   							

		Directional(const Directional& dl); 
		
		virtual Light* 									
		clone(void) const;			

		Directional& 									
		operator= (const Directional& rhs); 
			
		virtual											
		~Directional(void); 
				
		void
		scale_radiance(const float b);
		
		void
		set_color(const float c);
		
		void
		set_color(const RGBColor& c);
		
		void
		set_color(const float r, const float g, const float b); 		
			
		void
		set_direction(Vector3D d);						
		
		void
		set_direction(float dx, float dy, float dz);
		
		virtual Vector3D								
		get_direction(ShadeRec& sr);
				
		virtual RGBColor		
		L(ShadeRec& sr);	
		
	private:

		float		ls;			
		RGBColor	color;
		Vector3D	dir;		// direction the light comes from
};





inline void
Directional::scale_radiance(const float b) { 
	ls = b;
}


inline void
Directional::set_color(const float c) {
	color.r = c; color.g = c; color.b = c;
}



inline void
Directional::set_color(const RGBColor& c) {
	color = c;
}



inline void
Directional::set_color(const float r, const float g, const float b) {
	color.r = r; color.g = g; color.b = b;
}



inline void
Directional::set_direction(Vector3D d) {
	dir = d;
	dir.normalize();
}



inline void
Directional::set_direction(float dx, float dy, float dz) {
	dir.x = dx; dir.y = dy; dir.z = dz;
	dir.normalize();
}


#endif
