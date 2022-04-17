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

#include "../World/World.h"
#include "../Samplers/Regular.h"
#include "../Tracers/RayCast.h"
#include "../Cameras/Orthographic.h"
#include "../Lights/Ambient.h"
#include "../Lights/PointLight.h"
#include "../Materials/Matte.h"
#include "../GeometricObjects/Sphere.h"

void
World::build_figure_04_04(void) {
	int num_samples = 1;  // use 1 for 4.4(a) and 16 for 4.4(b)

	Regular* uniform_ptr = new Regular(num_samples);

	vp.set_hres(128);
	vp.set_vres(128);
	vp.set_pixel_size(1.0f);
	vp.set_sampler(uniform_ptr);

	background_color = RGBColor::black;
	tracer_ptr = new RayCast(this);

	Orthographic* orthographic_ptr = new Orthographic;
	orthographic_ptr->set_eye(Point3D(0.0f, 0.0f, 100.0f));
	orthographic_ptr->set_lookat(Point3D(0.0f));
	orthographic_ptr->compute_uvw();
	set_camera(orthographic_ptr);

	ambient_ptr = new Ambient;

	PointLight* light_ptr = new PointLight();
	light_ptr->set_location(Point3D(100.0f, 100.0f, 200.0f));
	light_ptr->scale_radiance(2.0f);
	add_light(light_ptr);

	Matte* matte_ptr = new Matte;
	matte_ptr->set_ka(0.2f);
	matte_ptr->set_kd(0.8f);
	matte_ptr->set_cd(RGBColor::yellow);

	Sphere*	sphere_ptr = new Sphere(Point3D(0.0), 13.0);
	sphere_ptr->set_material(matte_ptr);
	add_object(sphere_ptr);
}
