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


#include <utility>
#include "Ambient.h"



Ambient::Ambient (const Ambient& a)
	: 	Light(a),
		ls(a.ls),
		color(a.color) 		
{}



Ambient::Ambient (Ambient&& a) noexcept
	: 	Light(std::move(a)),
		ls(std::exchange(a.ls, 1.0f)),
		color(std::move(a.color)) 		
{}



Ambient& 
Ambient::operator= (const Ambient& a) {
	Light::operator= (a);
	
	ls 		= a.ls;
	color 	= a.color;
	
	return (*this);
}



Ambient& 
Ambient::operator= (Ambient&& a) noexcept {
	Light::operator= (std::move(a));
	
	ls 		= std::exchange(a.ls, 1.0f);
	color 	= std::move(a.color);
	
	return (*this);
}



Light* 
Ambient::clone(void) const {
	return (new Ambient(*this));
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




