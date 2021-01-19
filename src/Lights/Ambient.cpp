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

#include "Ambient.h"


Ambient::Ambient (void)
	: 	Light(),
		ls(1.0),
		color(1.0)			
{}



Ambient::Ambient (const Ambient& a)
	: 	Light(a),
		ls(a.ls),
		color(a.color) 		
{}



Light* 
Ambient::clone(void) const {
	return (new Ambient(*this));
}	



Ambient& 
Ambient::operator= (const Ambient& rhs) {
	if (this == &rhs) {
		return (*this);
	}
			
	Light::operator= (rhs);
	
	ls 		= rhs.ls;
	color 	= rhs.color;
	
	return (*this);
}



Ambient::~Ambient (void) {}



Vector3D								
Ambient::get_direction([[maybe_unused]] ShadeRec& s) {
	return (Vector3D(0.0));
}



RGBColor
Ambient::L([[maybe_unused]] ShadeRec& sr) {	
	return (ls * color);
}




