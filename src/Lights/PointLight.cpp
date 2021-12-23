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

#include "PointLight.h"


PointLight::PointLight(void)
	: 	Light(),
		ls(1.0f),
		color(1.0f),
		location(0.0f, 1.0f, 0.0f)
{}



PointLight::PointLight(const PointLight& dl)
	: 	Light(dl),
		ls(dl.ls),
		color(dl.color),
		location(dl.location)
{}



Light*
PointLight::clone(void) const {
	return (new PointLight(*this));
}



PointLight&
PointLight::operator= (const PointLight& rhs)
{
	if (this == &rhs) {
		return (*this);
	}

	Light::operator= (rhs);

	ls		= rhs.ls;
	color 	= rhs.color;
	location 	= rhs.location;

	return (*this);
}



PointLight::~PointLight(void) {}


Vector3D
PointLight::get_direction(ShadeRec& sr) {
	return (location - sr.hit_point).hat();
}


RGBColor
PointLight::L([[maybe_unused]] ShadeRec& s) {
	return (ls * color);
}

bool
PointLight::in_shadow(const Ray &ray, const ShadeRec &sr) const
{
    float t;
    int num_objects = sr.w.objects.size();
    float d = location.distance(ray.o);

    for (int j = 0; j < num_objects; j++) {
        if (sr.w.objects[j]->shadow_hit(ray, t) && t < d) {
            return true;
        }
    }

    return false;

}