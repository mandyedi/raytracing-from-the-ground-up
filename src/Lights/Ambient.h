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

#ifndef __AMBIENT__
#define __AMBIENT__

#include "Light.h"

class Ambient: public Light {
	public:
	
		Ambient(void);   							

		Ambient(const Ambient& a); 					 
	
		virtual Light* 									
		clone(void) const;	
		
		Ambient& 									
		operator= (const Ambient& rhs);									
		
		virtual 									
		~Ambient(void);
				
		void
		scale_radiance(const float b);
		
		void
		set_color(const float c);
		
		void
		set_color(const RGBColor& c);
		
		void
		set_color(const float r, const float g, const float b); 
		
		virtual Vector3D								
		get_direction(ShadeRec& s); 
		
		virtual RGBColor
		L(ShadeRec& s);
	
	private:
	
		float		ls;
		RGBColor	color;
};





inline void
Ambient::scale_radiance(const float b) { 
	ls = b;
}


inline void
Ambient::set_color(const float c) {
	color.r = c; color.g = c; color.b = c;
}



inline void
Ambient::set_color(const RGBColor& c) {
	color = c;
}



inline void
Ambient::set_color(const float r, const float g, const float b) {
	color.r = r; color.g = g; color.b = b;
}


#endif
