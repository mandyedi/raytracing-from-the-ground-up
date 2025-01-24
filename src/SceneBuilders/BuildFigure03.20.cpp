//  Copyright (C) Kevin Suffern 2000-2007.
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.
//  See the file COPYING.txt for the full license.

//  Copyright notice for changes since the originally published version:
//  Copyright (C) Eduárd Mándy 2019-2025
//  Though this C++ code was change in a large measure it still has the original copyright notice.
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.
//  See the file COPYING.txt for the full license.

#include "../GeometricObjects/Primitives/Plane.h"
#include "../GeometricObjects/Primitives/Sphere.h"
#include "../Tracers/MultipleObjects.h"
#include "../World/World.h"

void World::build_figure_03_20() {
    vp.set_hres(200);
    vp.set_vres(200);

    background_color = RGBColor::black;
    tracer_ptr = new MultipleObjects(this);

    Sphere* sphere_ptr = new Sphere;
    sphere_ptr->set_center(Point3D(0.0f, -25.0f, 0.0f));
    sphere_ptr->set_radius(80.0f);
    sphere_ptr->set_color(RGBColor::red);
    add_object(sphere_ptr);

    sphere_ptr = new Sphere(Point3D(0.0f, 30.0f, 0.0f), 60.0f);
    sphere_ptr->set_color(RGBColor::yellow);
    add_object(sphere_ptr);

    Plane* plane_ptr = new Plane(Point3D(0.0f), Normal(0.0f, 1.0f, 1.0f));
    plane_ptr->set_color(RGBColor::darkGreen);
    add_object(plane_ptr);
}
