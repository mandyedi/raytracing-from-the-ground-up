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

#include "Spherical.h"
#include "../Utilities/RGBColor.h"
#include "../Utilities/Point3D.h"
#include "../Utilities/Vector3D.h"
#include "../Utilities/Maths.h"
#include "../Samplers/Sampler.h"

Spherical::Spherical(void)
	:	Camera(),
		psi_max(120)
{}

Spherical::Spherical(const Spherical& c)
	: 	Camera(c),
		psi_max(120)
{}

Camera*
Spherical::clone(void) const {
	return (new Spherical(*this));
}

Spherical&
Spherical::operator= (const Spherical& rhs) {
	if (this == &rhs) {
		return (*this);
	}

	Camera::operator= (rhs);

	psi_max = rhs.psi_max;

	return (*this);
}

Spherical::~Spherical(void) {}

Vector3D
Spherical::ray_direction(	const Point2D& 	pp,
						const int 		hres,
						const int 		vres,
						const float 	s) const {

	// compute the normalized device coordinates

	Point2D pn(2.0f / (s * static_cast<float>(hres)) * pp.x, 2.0f / (s * static_cast<float>(vres)) * pp.y);

	// compute the angles lambda and psi in radians

	float lambda = pn.x * degreeToRadian(lambda_max);
	float psi = pn.y * degreeToRadian(psi_max);

	// compute the sherical azimuth and polar angles

	float phi = PI - lambda;
	float theta = 0.5f * PI - psi;
	
	float sin_phi = sinf(phi);
	float cos_phi = cosf(phi);
	float sin_theta = sinf(theta);
	float cos_theta = cosf(theta);

	Vector3D dir = sin_theta * sin_phi * u + cos_theta * v + sin_theta * cos_phi * w;

	return dir;
}

void
Spherical::render_scene(const World& wr) {
	RGBColor	L;
	ViewPlane	vp(wr.vp);
	int 		hres		= vp.hres;
	int 		vres 		= vp.vres;
	float		s 			= vp.s;
	Ray			ray;
	int 		depth 		= 0;
	Point2D 	sp; 					// sample point in [0, 1] X [0, 1]
	Point2D 	pp;						// sample point on the pixel

	ray.o = eye;
	float inv_num_samples = 1.0f / static_cast<float>(vp.num_samples);

	for (int r = 0; r < vres; r++)		// up
		for (int c = 0; c < hres; c++) {	// across
			L = RGBColor::black;

			for (int j = 0; j < vp.num_samples; j++) {
				sp = vp.sampler_ptr->sample_unit_square();
				pp.x = s * (c - 0.5f * hres + sp.x);
				pp.y = s * (r - 0.5f * vres + sp.y);
				ray.d = ray_direction(pp, hres, vres, s);

				L += wr.tracer_ptr->trace_ray(ray, depth);
			}

			L *= inv_num_samples;
			L *= exposure_time;
			wr.display_pixel(r, c, L);
		}


	wr.save_to_ppm();
}
