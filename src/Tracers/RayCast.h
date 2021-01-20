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

#ifndef __RAY_CAST__
#define __RAY_CAST__

#include "Tracer.h"

class RayCast: public Tracer {
	public:
		
		RayCast(void);
		
		explicit RayCast(World* _worldPtr);
				
		virtual RayCast*
		clone(void) const override;

		virtual											
		~RayCast(void);		

		virtual RGBColor	
		trace_ray(const Ray& ray) const override;

		virtual RGBColor	
		trace_ray(const Ray& ray, const int depth) const override;
};

#endif