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

#include "SingleSphere.h"
#include "../World/World.h"
#include "../Utilities/ShadeRec.h"


SingleSphere::SingleSphere(void)
	: Tracer()
{}


		
SingleSphere::SingleSphere(World* _worldPtr)
	: Tracer(_worldPtr)
{}



SingleSphere::~SingleSphere(void) {}



RGBColor	
SingleSphere::trace_ray(const Ray& ray) const {
	ShadeRec	sr(*world_ptr); 	// not used
	double    	t;  				// not used
	
	if (world_ptr->sphere.hit(ray, t, sr)) {	
		return (RGBColor::red);
	}
	else {
		return (RGBColor::black);
	}
}


