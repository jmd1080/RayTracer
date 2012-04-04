/*
 * GeometricObject.cpp
 *
 *  Created on: 1 Apr 2012
 */

#include "../Utilities/Constants.h"
#include "GeometricObject.h"


// default constructor

GeometricObject::GeometricObject(void)
	: material_ptr(NULL)
{}


// ---------------------------------------------------------------------- copy constructor

GeometricObject::GeometricObject (const GeometricObject& object) {
	if(object.material_ptr)
		material_ptr = object.material_ptr;
	else  material_ptr = NULL;
}


// ---------------------------------------------------------------------- assignment operator

GeometricObject&
GeometricObject::operator= (const GeometricObject& rhs) {
	if (this == &rhs)
		return (*this);

	if (rhs.material_ptr)
		material_ptr = rhs.material_ptr;

	return (*this);
}


// ---------------------------------------------------------------------- destructor

GeometricObject::~GeometricObject (void) {

}


// ---------------------------------------------------------------- set_material

void
GeometricObject::set_material(int mMtrl) {
	material = mMtrl;
}

void
GeometricObject::set_material_ptr(Material* mMtrl) {
	material_ptr = mMtrl;
}

