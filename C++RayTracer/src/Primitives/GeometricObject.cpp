/*
 * GeometricObject.cpp
 *
 *  Created on: 1 Apr 2012
 *      Author: James Davies
 */

#include "../Utilities/Constants.h"
#include "GeometricObject.h"


// default constructor

GeometricObject::GeometricObject(void)
	: material(NULL)
{}


// ---------------------------------------------------------------------- copy constructor

GeometricObject::GeometricObject (const GeometricObject& object) {
	if(object.material)
		material = object.material;
	else  material = NULL;
}


// ---------------------------------------------------------------------- assignment operator

GeometricObject&
GeometricObject::operator= (const GeometricObject& rhs) {
	if (this == &rhs)
		return (*this);

	if (rhs.material)
		material = rhs.material;

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

