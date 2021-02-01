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

#include "ThinLens.h"
#include "../Utilities/RGBColor.h"
#include "../Utilities/Point3D.h"
#include "../Utilities/Vector3D.h"
#include "../Samplers/Sampler.h"

ThinLens::ThinLens(void)
	:	Camera(),
		d(500),
		zoom(1.0)
{}



ThinLens::ThinLens(const ThinLens & c)
	: 	Camera(c),
		d(c.d),
		zoom(c.zoom)
{}



Camera*
ThinLens::clone(void) const {
	return (new ThinLens(*this));
}




ThinLens&
ThinLens::operator= (const ThinLens& rhs) {
	if (this == &rhs) {
		return (*this);
	}

	Camera::operator= (rhs);

	d 		= rhs.d;
	zoom	= rhs.zoom;

	return (*this);
}



ThinLens::~ThinLens(void) {}

void
ThinLens::set_sampler(Sampler* sp) {

	if (sampler_ptr) {
		delete sampler_ptr;
		sampler_ptr = NULL;
	}

	sampler_ptr = sp;
	sampler_ptr->map_samples_to_unit_disk();
}

Vector3D
ThinLens::ray_direction(const Point2D& pixel_point, const Point2D& lens_point) const {
	Point2D p(pixel_point.x * f / d, pixel_point.y * f / d);   // hit point on focal plane
	Vector3D dir = (p.x - lens_point.x) * u + (p.y - lens_point.y) * v - f * w;
	dir.normalize();

	return (dir);
}

void
ThinLens::render_scene(const World& w) {
	RGBColor	L;
	Ray			ray;
	ViewPlane	vp(w.vp);
	int 		depth 		= 0;

	Point2D sp;			// sample point in [0, 1] X [0, 1]
	Point2D pp;			// sample point on a pixel
	Point2D dp; 		// sample point on unit disk
	Point2D lp;			// sample point on lens

	vp.s /= zoom;

	float inv_num_samples = 1.0f / static_cast<float>(vp.num_samples);

	for (int r = 0; r < vp.vres; r++)			// up
		for (int c = 0; c < vp.hres; c++) {		// across
			L = RGBColor::black;

			for (int n = 0; n < vp.num_samples; n++) {
				sp = vp.sampler_ptr->sample_unit_square();
				pp.x = vp.s * (c - vp.hres / 2.0f + sp.x);
				pp.y = vp.s * (r - vp.vres / 2.0f + sp.y);

				dp = sampler_ptr->sample_unit_disk();
				lp = dp * lens_radius;

				ray.o = eye + lp.x * u + lp.y * v;
				ray.d = ray_direction(pp, lp);
				L += w.tracer_ptr->trace_ray(ray, depth);
			}

			L *= inv_num_samples;
			L *= exposure_time;
			w.display_pixel(r, c, L);
		}
}
