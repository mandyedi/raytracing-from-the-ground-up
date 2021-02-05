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

#ifndef __POINTLIGHT__
#define __POINTLIGHT__

#include "Light.h"
#include "../Utilities/Vector3D.h"
#include "../Utilities/Point3D.h"
#include "../Utilities/RGBColor.h"

#include "../World/World.h"			// you will need this later on for shadows
#include "../Utilities/ShadeRec.h"


class PointLight: public Light {
	public:

		PointLight(void);

		PointLight(const PointLight& dl);

		virtual Light*
		clone(void) const override;

		PointLight&
		operator= (const PointLight& rhs);

		virtual
		~PointLight(void);

		void
		scale_radiance(const float b);

		void
		set_color(const float c);

		void
		set_color(const RGBColor& c);

		void
		set_color(const float r, const float g, const float b);

		void
		set_location(const Point3D& p);

		void
		set_location(float x, float y, float z);

		void
		set_direction(float dx, float dy, float dz);

		virtual Vector3D
		get_direction(ShadeRec& sr) override;

		virtual RGBColor
		L(ShadeRec& sr) override;

	private:

		float		ls;
		RGBColor	color;
		Point3D location;
};





inline void
PointLight::scale_radiance(const float b) {
	ls = b;
}


inline void
PointLight::set_color(const float c) {
	color.r = c; color.g = c; color.b = c;
}



inline void
PointLight::set_color(const RGBColor& c) {
	color = c;
}



inline void
PointLight::set_color(const float r, const float g, const float b) {
	color.r = r; color.g = g; color.b = b;
}



inline void
PointLight::set_location(const Point3D& p) {
	location = p;
}



inline void
PointLight::set_location(float x, float y, float z) {
	location.x = x;
	location.y = y;
	location.z = z;
}

#endif
