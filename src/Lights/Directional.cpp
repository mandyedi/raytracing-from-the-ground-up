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

#include "Directional.h"


Directional::Directional(void)
	: 	Light(),
		ls(1.0),
		color(1.0),
		dir(0, 1, 0)			
{}



Directional::Directional(const Directional& dl)
	: 	Light(dl),
		ls(dl.ls),
		color(dl.color),
		dir(dl.dir)  		
{}



Light* 
Directional::clone(void) const {
	return (new Directional(*this));
}



Directional& 
Directional::operator= (const Directional& rhs) 	
{
	if (this == &rhs) {
		return (*this);
	}
			
	Light::operator= (rhs);
	
	ls		= rhs.ls;
	color 	= rhs.color;
	dir 	= rhs.dir;

	return (*this);
}



Directional::~Directional(void) {}


Vector3D								
Directional::get_direction([[maybe_unused]] ShadeRec& sr) {
	return (dir);
}	


RGBColor
Directional::L([[maybe_unused]] ShadeRec& s) {	
	return (ls * color);
}


