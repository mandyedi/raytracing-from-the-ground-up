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

#ifndef __BOX__
#define __BOX__

#include "GeometricObject.h"
#include "../Utilities/Ray.h"
#include "../Utilities/Point3D.h"

class ShadeRec;

class Box : public GeometricObject {
	public:
		double x0 = -1.0;
		double x1 = 1.0;
		double y0 = -1.0;
		double y1 = 1.0;
		double z0 = -1.0;
		double z1 = 1.0;

		Box(void) = default;

		explicit Box(	const double x0, const double x1,
				const double y0, const double y1,
				const double z0, const double z1);

		explicit Box(const Point3D p0, const Point3D p1);

		~Box(void) = default;

		Box(const Box& box);

		Box(Box&& box) noexcept;

		Box&
		operator= (const Box& box);

		Box &
		operator= (Box&& box) noexcept;

		Box*
		clone(void) const override;

		bool
		hit(const Ray& ray, double& tmin, ShadeRec& sr) const;

		bool
		inside(const Point3D& point) const;

	private:
		Normal
		get_normal(const int face_hit) const;
};

#endif
