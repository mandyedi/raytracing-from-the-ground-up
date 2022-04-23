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
#include "../Tracers/SingleSphere.h"
#include "../GeometricObjects/Primitives/Sphere.h"

void
World::build_figure_03_18() {
    vp.set_hres(200);
    vp.set_vres(200);
    vp.set_gamma(1.0f);

    background_color = RGBColor::black;
    tracer_ptr = new SingleSphere(this);

    Sphere *sphere = new Sphere;
    sphere->set_center(Point3D(0.0f));
    sphere->set_radius(85.0f);
    add_object(sphere);
}
