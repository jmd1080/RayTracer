/*
 * Directional.cpp
 *
 *  Created on: 4 Apr 2012
 *      Author: jamie
 */

#include "Directional.h"
#include "../World/World.h"
#include <stdio.h>

// Default constructor

Directional::Directional(void):
	Light(),
	cl(RGBColor()),
	d(Vector3D(0))
{}

// Constructor

Directional::Directional(Vector3D dir, RGBColor cIn):
		Light(),
		cl(cIn),
		d(dir)
{}

// Copy constructor

Directional::Directional(const Directional& directional):
		Light(directional),
		d(directional.d),
		cl(directional.cl)
{}

Directional&
Directional::operator= (const Directional& rhs)
{
	Light::operator= (rhs);
	d = rhs.d;
	cl = rhs.cl;
	return (*this);
}

RGBColor
Directional::get_intensity(ShadeRec& sr) const
{
	//printf("GLOW\n");

	RGBColor result = cl * (sr.normal * d);
	//printf("GLOW12\n");

	// If self occlusion return 0
	if (cl.r < 0 || cl.g < 0 || cl.b < 0)
		result = RGBColor(0.0);

	// Check for shadows

	Ray shadowRay;

	shadowRay.o = sr.local_hit_point;
	shadowRay.d = d;

	ShadeRec s(sr.w.hit_objects(shadowRay));

	if (s.hit_an_object)
		return RGBColor(0.0);

	return result;
}

void
Directional::set_intensity(RGBColor In)
{
	cl = In;
}

float
Directional::get_rv(ShadeRec& sr)
{
	Vector3D R = d - 2* (d*sr.normal) * sr.normal;

	float rv =  R*sr.ray.d;

	if (rv < 0)
		rv = 0;

	return R*sr.ray.d;
}

void
Directional::set_dir(const Vector3D& dir) {
	d = dir;
	d.normalize();
}
