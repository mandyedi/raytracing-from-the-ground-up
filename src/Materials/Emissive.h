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

#ifndef __EMISSIVE__
#define __EMISSIVE__

#include "../Materials/Material.h"

class Emissive: public Material {
	private:
	
		float		ls;		// radiance scaling factor
		RGBColor 	ce;		// color
	
	public:
	
		Emissive(void);

		Emissive(const Emissive& m);
		
		virtual Material*
		clone(void) const override;

		Emissive& 
		operator= (const Emissive& rhs);

		~Emissive(void);	
	
		virtual RGBColor
		shade(ShadeRec& sr);
	
		virtual RGBColor
		area_light_shade(ShadeRec& sr);

		void
		set_ce(float r, float g, float b);

		void
		set_ce(const RGBColor &color);
		
		virtual RGBColor
		get_Le(ShadeRec& sr) const;

		void
		scale_radiance(float _ls);
};

inline void
Emissive::set_ce(float r, float g, float b) {
    ce.r = r; ce.g = g; ce.b = b;
}

inline void
Emissive::set_ce(const RGBColor &color) {
    ce.r = color.r; ce.g = color.g; ce.b = color.b;
}

inline RGBColor
Emissive::get_Le(ShadeRec &sr) const {
    return ls * ce;
}

inline void
Emissive::scale_radiance(float _ls) {
    ls = _ls;
}

#endif