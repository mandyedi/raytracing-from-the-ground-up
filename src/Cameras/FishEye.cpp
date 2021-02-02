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

#include "FishEye.h"
#include "../Utilities/RGBColor.h"
#include "../Utilities/Point3D.h"
#include "../Utilities/Vector3D.h"
#include "../Samplers/Sampler.h"

FishEye::FishEye(void)
	:	Camera(),
		psi_max(120)
{}

FishEye::FishEye(const FishEye& c)
	: 	Camera(c),
		psi_max(120)
{}

Camera*
FishEye::clone(void) const {
	return (new FishEye(*this));
}

FishEye&
FishEye::operator= (const FishEye& rhs) {
	if (this == &rhs) {
		return (*this);
	}

	Camera::operator= (rhs);

	psi_max = rhs.psi_max;

	return (*this);
}

FishEye::~FishEye(void) {}

Vector3D
FishEye::ray_direction(	const Point2D& 	pp,
						const int 		hres,
						const int 		vres,
						const float 	s,
						float& 			r_squared) const {

	// compute the normalized device coordinates

	Point2D pn(2.0f / (s * static_cast<float>(hres)) * pp.x, 2.0f / (s * static_cast<float>(vres)) * pp.y);
	r_squared = pn.x * pn.x + pn.y * pn.y;

	if (r_squared <= 1.0) {
		float r 		= sqrtf(r_squared);
		float psi 		= r * psi_max * PI_ON_180;
		float sin_psi 	= sinf(psi);
		float cos_psi 	= cosf(psi);
		float sin_alpha = pn.y / r;
		float cos_alpha = pn.x / r;
		Vector3D dir 	= sin_psi * cos_alpha * u +  sin_psi * sin_alpha * v - cos_psi * w;

		return (dir);
	}
	else
		return (Vector3D(0.0));
}

void
FishEye::render_scene(const World& wr) {
	RGBColor	L;
	ViewPlane	vp(wr.vp);
	int 		hres		= vp.hres;
	int 		vres 		= vp.vres;
	float		s 			= vp.s;
	Ray			ray;
	int 		depth 		= 0;
	Point2D 	sp; 					// sample point in [0, 1] X [0, 1]
	Point2D 	pp;						// sample point on the pixel
	float		r_squared;				// sum of squares of normalised device coordinates

	ray.o = eye;
	float inv_num_samples = 1.0f / static_cast<float>(vp.num_samples);

	for (int r = 0; r < vres; r++)		// up
		for (int c = 0; c < hres; c++) {	// across
			L = RGBColor::black;

			for (int j = 0; j < vp.num_samples; j++) {
				sp = vp.sampler_ptr->sample_unit_square();
				pp.x = s * (c - 0.5f * hres + sp.x);
				pp.y = s * (r - 0.5f * vres + sp.y);
				ray.d = ray_direction(pp, hres, vres, s, r_squared);

				if (r_squared <= 1.0) {
					L += wr.tracer_ptr->trace_ray(ray, depth);
				}
			}

			L *= inv_num_samples;
			L *= exposure_time;
			wr.display_pixel(r, c, L);
		}


	wr.save_to_ppm();
} 
