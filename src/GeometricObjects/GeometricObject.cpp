#include "Constants.h"
#include "Material.h"
#include "GeometricObject.h"




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


								