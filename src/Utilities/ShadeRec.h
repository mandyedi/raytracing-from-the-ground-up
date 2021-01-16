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

#ifndef __SHADE_REC__
#define __SHADE_REC__

#include <vector>

class Material;
class World;

#include "Point3D.h"
#include "Normal.h"
#include "Ray.h"
#include "RGBColor.h"

class ShadeRec {
	public:
	
		bool				hit_an_object;
		Material* 			material_ptr;		// Pointer to the nearest object's material
		Point3D 			hit_point;			// World coordinates of intersection
		Point3D				local_hit_point;	// World coordinates of hit point on generic object (used for texture transformations)
		Normal				normal;				// Normal at hit point
		Ray					ray;
		int					depth;				// recursion depth
		double				t;					// ray parameter
		World&				w;
		RGBColor            color;
				
		ShadeRec(World& wr);
		
		ShadeRec(const ShadeRec& sr);
};

#endif