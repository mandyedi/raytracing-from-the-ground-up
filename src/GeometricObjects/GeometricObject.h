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

#ifndef __GEOMETRIC_OBJECT__
#define __GEOMETRIC_OBJECT__

class Material;
	
#include "../Utilities/Point3D.h"
#include "../Utilities/Ray.h"
#include "../Utilities/ShadeRec.h"



class GeometricObject {	
	
	public:	

		GeometricObject(void);
		
		GeometricObject(const GeometricObject& object);
	
		virtual GeometricObject*
		clone(void) const = 0;

		virtual
		~GeometricObject (void);
			
		virtual bool
		hit(const Ray& ray, double& t, ShadeRec& s) const = 0;
				
		Material*
		get_material(void) const;

		virtual void
		set_material(Material* mPtr);

		void
		set_color(const RGBColor &c);

		void
		set_color(const float r, const float g, const float b);

		RGBColor
		get_color(void);
	
	protected:
	
		mutable Material*   material_ptr;   	// mutable allows Compound::hit, Instance::hit and Grid::hit to assign to material_ptr. hit functions are const
		RGBColor   			color;

		GeometricObject&
		operator= (const GeometricObject& rhs);
};



inline Material* 
GeometricObject::get_material(void) const {
	return (material_ptr);
}

inline void
GeometricObject::set_color(const RGBColor &c) {
	color = c;
}

inline void
GeometricObject::set_color(const float r, const float g, const float b) {
	color.r = r;
	color.b = b;
	color.g = g;
}

inline RGBColor
GeometricObject::get_color(void) {
	return (color);
}

#endif