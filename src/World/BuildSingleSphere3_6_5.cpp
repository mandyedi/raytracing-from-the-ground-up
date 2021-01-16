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

#include "World.h"
#include "../Utilities/RGBColor.h"

void
World::build_single_sphere_3_6_5(void) {
	vp.set_hres(200);
	vp.set_vres(200);
	vp.set_pixel_size(1.0);

	background_color = RGBColor::black;
	tracer_ptr = new SingleSphere(this);

	sphere.set_center(0.0);
	sphere.set_radius(85.0);
}

void
World::render_single_sphere_3_6_5(void) {
	RGBColor	pixel_color;
	Ray			ray;
	double		zw = 100.0;
	double		x, y;

	ray.d = Vector3D(0, 0, -1);

	for ( int r = 0; r < vp.vres; r++ ) {
		for ( int c = 0; c < vp.hres; c++ ) {
			x = vp.s * (static_cast<double>(c) - 0.5 * (static_cast<double>(vp.hres) - 1.0));
			y = vp.s * (static_cast<double>(r) - 0.5 * (static_cast<double>(vp.vres) - 1.0));
			ray.o = Point3D(x, y, zw);
			pixel_color = tracer_ptr->trace_ray(ray);
			display_pixel(r, c, pixel_color);
		}
	}

	save_to_ppm();
}