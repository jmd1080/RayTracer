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
#include "../Utilities/ShadeRec.h"
#include <stdio.h>
#include "../Material/Material.h"

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
CSG::union_hit(const Ray& ray, double& tmin, double& tmax, ShadeRec& sr) const
{
	double amin, amax, bmin, bmax;
	ShadeRec srA = ShadeRec(sr.w);
	ShadeRec srB = ShadeRec(sr.w);
	bool ahit = a->hit(ray, amin,amax,srA);
	bool bhit = b->hit(ray, bmin,bmax,srB);

	// cope with non-hits
	if (!ahit)
	{
		amin = bmin + 1;
	}
	if (!bhit)
	{
		bmin = amin + 1;
	}

	if(ahit || bhit)
	{
		if (bmin < amin)
		{
			sr.normal = srB.normal;
			sr.hit_point = srB.hit_point;
			tmin = bmin;
			sr.t = bmin;
		}
		else
		{
			sr.normal = srA.normal;
			sr.hit_point = srA.hit_point;
			tmin = amin;
			sr.t = amin;
		}
		if (amax > bmax)
		{
			tmax = amax;
			sr.normal_max = srA.normal_max;
		}
		else
		{
			tmax = bmax;
			sr.normal_max = srB.normal_max;
		}
		return true;
	}
	else
		return false;
}

bool
CSG::sub_hit(const Ray& ray, double& tmin, double& tmax, ShadeRec& sr) const
{

	return false;
}

bool
CSG::intersect_hit(const Ray& ray, double& tmin, double& tmax, ShadeRec& sr) const
{
	double amin, amax, bmin, bmax;
	ShadeRec srA = ShadeRec(sr.w);
	ShadeRec srB = ShadeRec(sr.w);
	bool ahit = a->hit(ray, amin,amax,srA);
	bool bhit = b->hit(ray, bmin,bmax,srB);
	if(ahit || bhit)
	{
		if ((bmin< amin ) && (bmax> amin ) )
		{
			tmin = amin;
			sr.local_hit_point = srA.local_hit_point;
			sr.normal = srA.normal;
			return true;
		}
		if ((amin< bmin ) && (amax> bmin ) )
		{
			tmin = bmin;
			sr.local_hit_point = srB.local_hit_point;
			sr.normal = srB.normal;
			sr.material_ptr = srB.material_ptr;
			return true;
		}
	}
	return false;
}


//---------------------------------------------------------------- hit

bool
CSG::hit(const Ray& ray, double& tmin, double& tmax, ShadeRec& sr) const {
	switch (op) {
	case UNION:
		return union_hit(ray,tmin,tmax, sr);
		break;
	case SUBTRACTION:
		return sub_hit(ray,tmin,tmax, sr);
		break;
	case INTERSECTION:
		return intersect_hit(ray, tmin, tmax, sr);
		break;
	}
	return (false);
}
