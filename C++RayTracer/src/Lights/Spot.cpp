/*
 * Spot.cpp
 *
 *  Created on: 7 Apr 2012
 *      Author: James Davies
 */

#include "Spot.h"
#include "../World/World.h"
#include <stdio.h>
#include <math.h>

// Default constructor

Spot::Spot(void):
	Light(),
	cl(RGBColor()),
	p(Point3D(0)),
	d(Vector3D(0)),
	arc(0)
{}

// Constructor

Spot::Spot(Point3D pnt, RGBColor cIn, Vector3D din, float arcin):
		Light(),
		cl(cIn),
		p(pnt),
		d(din),
		arc(arcin)
{}

// Copy constructor

Spot::Spot(const Spot& Spot):
		Light(Spot),
		p(Spot.p),
		cl(Spot.cl),
		d(Spot.d),
		arc(Spot.arc)
{}

Spot&
Spot::operator= (const Spot& rhs)
{
	Light::operator= (rhs);
	p = rhs.p;
	cl = rhs.cl;
	return (*this);
}

RGBColor
Spot::get_intensity(ShadeRec& sr) const
{
	Vector3D dir = p - sr.hit_point;
	float dist = dir.length();

	dir.normalize();

	float theta = acos(-1*(dir.x*d.x+dir.y*d.y+dir.z*d.z));

	if (theta > arc)
		return RGBColor(0);


	RGBColor result = cl * (sr.normal * dir);

	// If self occlusion return 0
	if (cl.r < 0 || cl.g < 0 || cl.b < 0)
		result = RGBColor(0);

	// Check for shadows

	Ray shadowRay;

	shadowRay.o = sr.local_hit_point;
	shadowRay.d = dir;

	ShadeRec s(sr.w.hit_objects(shadowRay));

	if (s.hit_an_object)
	{
		if (s.local_hit_point * dir < kEpsilon)
			return result*(s.inv_opacity);
	}

	return result;
}

void
Spot::set_intensity(RGBColor In)
{
	cl = In;
}

float
Spot::get_rv(ShadeRec& sr)
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
Spot::set_loc(const Point3D& pnt) {
	p = pnt;
}
