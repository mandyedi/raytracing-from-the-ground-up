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

#ifndef __BRDF__
#define __BRDF__


#include <math.h>

#include "../Utilities/RGBColor.h"
#include "../Utilities/Vector3D.h"
#include "../Utilities/ShadeRec.h"

class BRDF {
	public:
	
		BRDF(void);						
		
		BRDF(const BRDF& object);
		
		virtual BRDF*
		clone(void) const = 0;
		
		virtual
		~BRDF(void);
								
		virtual RGBColor
		f(const ShadeRec& sr, const Vector3D& wo, const Vector3D& wi) const;
		
		virtual RGBColor
		sample_f(const ShadeRec& sr, const Vector3D& wo, Vector3D& wi) const;
		
		virtual RGBColor
		sample_f(const ShadeRec& sr, const Vector3D& wo, Vector3D& wi, float& pdf) const;
		
		virtual RGBColor
		rho(const ShadeRec& sr, const Vector3D& wo) const;
		
			
	protected:
	
		BRDF&							
		operator= (const BRDF& rhs);
};

#endif