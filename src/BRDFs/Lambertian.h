//  Copyright (C) Kevin Suffern 2000-2007.
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.
//  See the file COPYING.txt for the full license.

//  Copyright notices for changes since the originally published version:
//  Copyright (C) Eduárd Mándy 2019-2021
//  Though this C++ code was change in a large measure it still has the original copyright notices.
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.
//  See the file COPYING.txt for the full license.

#ifndef __LAMBERTIAN__
#define __LAMBERTIAN__

#include "BRDF.h"

class Lambertian: public BRDF {
	public:
	
		Lambertian(void);
		
		Lambertian(const Lambertian& lamb);
		
		virtual Lambertian*
		clone(void) const;
		
		~Lambertian(void);
		
		Lambertian& 
		operator= (const Lambertian& rhs);
		
		virtual RGBColor
		f(const ShadeRec& sr, const Vector3D& wo, const Vector3D& wi) const;
		
		virtual RGBColor
		rho(const ShadeRec& sr, const Vector3D& wo) const;
			
		void
		set_ka(const float ka);	
				
		void
		set_kd(const float kd);
		
		void
		set_cd(const RGBColor& c);
		
		void													
		set_cd(const float r, const float g, const float b);
		
		void													
		set_cd(const float c);
					
	private:
	
		float		kd;
		RGBColor 	cd;
};





inline void
Lambertian::set_ka(const float k) {
	kd = k;
}




inline void
Lambertian::set_kd(const float k) {
	kd = k;
}



inline void
Lambertian::set_cd(const RGBColor& c) {
	cd = c;
}



inline void													
Lambertian::set_cd(const float r, const float g, const float b) {
	cd.r = r; cd.g = g; cd.b = b;
}



inline void													
Lambertian::set_cd(const float c) {
	cd.r = c; cd.g = c; cd.b = c;
}

#endif
