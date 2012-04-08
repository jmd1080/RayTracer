/*
 * CSG.cpp
 *
 *  Created on: 8 Apr 2012
 *      Author: James Davies
 */

// This file contains the definition of the class CSG

#include "CSG.h"
#include "../Utilities/Constants.h"
#include "math.h"

// ---------------------------------------------------------------- default constructor

CSG::CSG(void)
: 	GeometricObject(),
  	a(NULL),
  	b(NULL),
  	op(0)
{}


// ---------------------------------------------------------------- constructor

CSG::CSG(GeometricObject *aIn, GeometricObject *bIn, int opIn)
: 	GeometricObject(),
  	a(aIn),
  	b(bIn),
  	op(opIn)
{}


// ---------------------------------------------------------------- clone

CSG*
CSG::clone(void) const {
	return (new CSG(*this));
}


// ---------------------------------------------------------------- copy constructor

CSG::CSG (const CSG& csg)
: 	GeometricObject(csg),
  	a(csg.a),
  	b(csg.b),
  	op(csg.op)
{}



// ---------------------------------------------------------------- assignment operator

CSG&
CSG::operator= (const CSG& rhs)
{
	if (this == &rhs)
		return (*this);

	GeometricObject::operator= (rhs);

	a 	= rhs.a;
	b	= rhs.b;
	op	= rhs.op;

	return (*this);
}


// ---------------------------------------------------------------- destructor

//CSG::~CSG(void) {}
//TODO Create proper destructor

bool
CSG::union_hit(const Ray& ray, double& tmin, ShadeRec& sr) const
{
	return false;
}

bool
CSG::sub_hit(const Ray& ray, double& tmin, ShadeRec& sr) const
{
	return false;
}

bool
CSG::intersect_hit(const Ray& ray, double& tmin, ShadeRec& sr) const
{
	return false;
}


//---------------------------------------------------------------- hit

bool
CSG::hit(const Ray& ray, double& tmin, ShadeRec& sr) const {
	switch (op) {
	case UNION:
		return union_hit(ray,tmin,sr);
		break;
	case SUBTRACTION:
		return sub_hit(ray,tmin,sr);
		break;
	case INTERSECTION:
		return intersect_hit(ray, tmin, sr);
		break;
	}
	return (false);
}
