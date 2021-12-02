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

#ifndef __RECTANGLE__
#define __RECTANGLE__

#include "GeometricObject.h"

class Sampler;

class Rectangle: public GeometricObject {	
	public:
		
		Rectangle(void);   									
				
		Rectangle(const Point3D& _p0, const Vector3D& _a, const Vector3D& _b);
		
		Rectangle(const Point3D& _p0, const Vector3D& _a, const Vector3D& _b, const Normal& n);
		
		virtual Rectangle* 										
		clone(void) const;
	
		Rectangle(const Rectangle& r); 						

		virtual													
		~Rectangle(void);   									

		Rectangle& 												
		operator= (const Rectangle& rhs);
		
		// todo: implement it, when BBox class is ready
		// BBox
		// get_bounding_box(void);				
	
		virtual bool 												 
		hit(const Ray& ray, double& t, ShadeRec& s) const;	
				
		
		// the following functions are used when the rectangle is a light source
		
				
		Point3D 											
		sample(void) override;
		
		Normal 																
		get_normal(const Point3D& p) override;		
		
		float												
		pdf(const ShadeRec& sr) override;
		
	private:
	
		Point3D 		p0;   			// corner vertex 
		Vector3D		a;				// side
		Vector3D		b;				// side
		double			a_len_squared;	// square of the length of side a
		double			b_len_squared;	// square of the length of side b
		Normal			normal;	
		
		float			area;			// for rectangular lights
		float			inv_area;		// for rectangular lights
		Sampler*		sampler_ptr;	// for rectangular lights 	
		
		static const double kEpsilon;   											
};

#endif
