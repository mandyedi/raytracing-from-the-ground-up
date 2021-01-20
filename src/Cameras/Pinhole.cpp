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

#include <math.h>

#include "Pinhole.h"
#include "../Utilities/RGBColor.h" 
#include "../Utilities/Point3D.h"
#include "../Utilities/Vector3D.h"
#include "../Samplers/Sampler.h"


Pinhole::Pinhole(void)		
	:	Camera(),
		d(500),
		zoom(1.0)
{}



Pinhole::Pinhole(const Pinhole& c)   		
	: 	Camera(c),
		d(c.d),
		zoom(c.zoom)
{}



Camera* 
Pinhole::clone(void) const {
	return (new Pinhole(*this));
}




Pinhole& 
Pinhole::operator= (const Pinhole& rhs) { 	
	if (this == &rhs) {
		return (*this);
	}
		
	Camera::operator= (rhs);

	d 		= rhs.d;
	zoom	= rhs.zoom;

	return (*this);
}



Pinhole::~Pinhole(void) {}	



Vector3D
Pinhole::get_direction(const Point2D& p) const {
	Vector3D dir = p.x * u + p.y * v - d * w;
	dir.normalize();
	
	return(dir);
}




void 												
Pinhole::render_scene(const World& w) {
	RGBColor	L;
	ViewPlane	vp(w.vp);	 								
	Ray			ray;
	int 		depth = 0;
	Point2D		sp;		// sample point in [0, 1] x [0, 1]
	Point2D 	pp;		// sample point on a pixel
		
	vp.s /= zoom;
	ray.o = eye;

	float inv_num_samples = 1.0f / static_cast<float>(vp.num_samples);
		
	for (int row = 0; row < vp.vres; row++) {			// up
		for (int column = 0; column < vp.hres; column++) {		// across 					
			L = RGBColor::black; 
			
			for (int j = 0; j < vp.num_samples; j++) {
				sp = vp.sampler_ptr->sample_unit_square();
				pp.x = vp.s * (column - 0.5f * vp.hres + sp.x);
				pp.y = vp.s * (row - 0.5f * vp.vres + sp.y);
				ray.d = get_direction(pp);
				L += w.tracer_ptr->trace_ray(ray, depth);
			}
											
			L *= inv_num_samples;
			L *= exposure_time;
			w.display_pixel(row, column, L);
		}
	}
	
	w.save_to_ppm();
}


