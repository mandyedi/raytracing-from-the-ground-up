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

#ifndef __AMBIENTOCCLUDER__
#define __AMBIENTOCCLUDER__

#include "Light.h"
#include "../Utilities/Vector3D.h"
#include "../Utilities/Point3D.h"
#include "../Utilities/RGBColor.h"

#include "../World/World.h"			// you will need this later on for shadows
#include "../Utilities/ShadeRec.h"

class Sampler;

class AmbientOccluder: public Light {
	public:
	
		AmbientOccluder(void);

		AmbientOccluder(const AmbientOccluder& other);

		virtual Light*
		clone(void) const override;

		AmbientOccluder&
		operator= (const AmbientOccluder& other);

		virtual
		~AmbientOccluder(void);
	
		void
		set_sampler(Sampler* s_ptr);
	
		virtual Vector3D						
		get_direction(ShadeRec& sr);
	
		virtual bool									
		in_shadow(const Ray& ray, const ShadeRec& sr) const;
	
		virtual RGBColor
		L(ShadeRec& sr);

		void
	    scale_radiance(const float s);

	    void
	    set_min_amount(const float f);
	
	private:
	
		float		ls;
		RGBColor	color;
		float 		min_amount;	    
		Vector3D 	u, v, w;		
		Sampler*	sampler_ptr;
};

inline void
AmbientOccluder::scale_radiance(const float s) {
    ls = s;
}

inline void
AmbientOccluder::set_min_amount(const float m) {
    min_amount = m;
}

#endif