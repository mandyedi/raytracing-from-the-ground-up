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

#ifndef __PHONG__
#define __PHONG__

#include "../Materials/Material.h"
#include "../BRDFs/Lambertian.h"
#include "../BRDFs/GlossySpecular.h"


class Phong: public Material {
	public:

		Phong(void);

		Phong(const Phong& m);

		virtual Material *
		clone(void) const override;

		Phong&
		operator= (const Phong& rhs);

		~Phong(void);

		void
		set_ka(const float k);

		void
		set_kd(const float k);

		void
		set_cd(const RGBColor c);

		void
		set_cd(const float r, const float g, const float b);

		void
		set_cd(const float c);

		void
		set_ks(const float ks);

		void
		set_exp(const float exp);

		void
		set_cs(const RGBColor &c);

		void
		set_cs(const float r, const float g, const float b);

		void
		set_cs(const float c);

		virtual RGBColor
		shade(ShadeRec& sr) override;

		virtual RGBColor
		area_light_shade(ShadeRec &sr);

	private:

		Lambertian     *ambient_brdf;
		Lambertian     *diffuse_brdf;
		GlossySpecular *specular_brdf;
};



// there is no Lambertian::ka data member because ambient reflection is diffuse reflection
inline void
Phong::set_ka(const float ka) {
	ambient_brdf->set_kd(ka);
}


// this also sets Lambertian::kd, but for a different Lambertian object
inline void
Phong::set_kd (const float kd) {
	diffuse_brdf->set_kd(kd);
}



inline void
Phong::set_cd(const RGBColor c) {
	ambient_brdf->set_cd(c);
	diffuse_brdf->set_cd(c);
}



inline void
Phong::set_cd(const float r, const float g, const float b) {
	ambient_brdf->set_cd(r, g, b);
	diffuse_brdf->set_cd(r, g, b);
}


inline void
Phong::set_cd(const float c) {
	ambient_brdf->set_cd(c);
	diffuse_brdf->set_cd(c);
}

inline void
Phong::set_ks(const float k) {
	specular_brdf->set_ks(k);
}



inline void
Phong::set_exp(const float e) {
	specular_brdf->set_exp(e);
}



inline void
Phong::set_cs(const RGBColor &c) {
	specular_brdf->set_cs(c);
}



inline void
Phong::set_cs(const float r, const float g, const float b) {
	specular_brdf->set_cs(r, g, b);
}



inline void
Phong::set_cs(const float c) {
	specular_brdf->set_cs(c);
}

#endif
