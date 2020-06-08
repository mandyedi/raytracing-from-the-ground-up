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