/*
 * Point.cpp
 *
 *  Created on: 7 Apr 2012
 *      Author: James Davies
 */

#include "Point.h"
#include "../World/World.h"
#include <stdio.h>

// Default constructor

Point::Point(void):
	Light(),
	cl(RGBColor()),
	p(Point3D(0))
{}

// Constructor

Point::Point(Point3D pnt, RGBColor cIn):
		Light(),
		cl(cIn),
		p(pnt)
{}

// Copy constructor

Point::Point(const Point& Point):
		Light(Point),
		p(Point.p),
		cl(Point.cl)
{}

Point&
Point::operator= (const Point& rhs)
{
	Light::operator= (rhs);
	p = rhs.p;
	cl = rhs.cl;
	return (*this);
}

RGBColor
Point::get_intensity(ShadeRec& sr) const
{
	Vector3D d = p - sr.hit_point;
	d.normalize();
	RGBColor result = cl * (sr.normal * d);

	// If self occlusion return 0
	if (cl.r < 0 || cl.g < 0 || cl.b < 0)
		result = RGBColor(0);

	// Check for shadows

	Ray shadowRay;

	shadowRay.o = sr.local_hit_point;
	shadowRay.d = d;

	ShadeRec s(sr.w.hit_objects(shadowRay));

	//if (s.hit_an_object)
		//return result*(s.inv_opacity);

	return result;
}

void
Point::set_intensity(RGBColor In)
{
	cl = In;
}

float
Point::get_rv(ShadeRec& sr)
{
	Vector3D d = p - sr.hit_point;
	d.normalize();
	Vector3D R = d - 2* (d*sr.normal) * sr.normal;

	float rv =  R*sr.ray.d;

	if (rv < 0)
		rv = 0;

	return R*sr.ray.d;
}

void
Point::set_loc(const Point3D& pnt) {
	p = pnt;
}
