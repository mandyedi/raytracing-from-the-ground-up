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

#include "../Utilities/Constants.h"
#include "../Materials/Material.h"
#include "../GeometricObjects/GeometricObject.h"




GeometricObject::GeometricObject(void)
	: material_ptr(NULL)
{}



GeometricObject::GeometricObject (const GeometricObject& object) {
	if (object.material_ptr) {
		material_ptr = object.material_ptr->clone(); 
	}
	else {
		material_ptr = NULL;
	}
}	



GeometricObject&														
GeometricObject::operator= (const GeometricObject& rhs) {
	if (this == &rhs) {
		return (*this);
	}
			
	if (material_ptr) {
		delete material_ptr;
		material_ptr = NULL;
	}

	if (rhs.material_ptr) {
		material_ptr = rhs.material_ptr->clone();
	}

	return (*this);
}



GeometricObject::~GeometricObject (void) {	
	if (material_ptr) {
		delete material_ptr;
		material_ptr = NULL;
	}
}



void 
GeometricObject::set_material(Material* mPtr) {
	material_ptr = mPtr;
}


								