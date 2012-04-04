/*
 * Directional.cpp
 *
 *  Created on: 4 Apr 2012
 *      Author: jamie
 */

#include "Directional.h"
#include <stdio.h>

// Default constructor

Directional::Directional(void):
	Light(),
	Il(0),
	d(Vector3D(0))
{}

// Constructor

Directional::Directional(Vector3D dir, float In):
		Light(),
		Il(In),
		d(dir)
{}

// Copy constructor

Directional::Directional(const Directional& directional):
		Light(directional),
		d(directional.d),
		Il(directional.Il)
{}

Directional&
Directional::operator= (const Directional& rhs)
{

	Light::operator= (rhs);
	d = rhs.d;
	return (*this);
}

float
Directional::get_intensity(ShadeRec& sr) const
{
	double result = Il * sr.normal * d;

	// If self occlusion return 0
	if (result < 0)
		result = 0;

	return result;
}

void
Directional::set_intensity(float In)
{
	Il = In;
}

void
Directional::set_dir(const Vector3D& dir) {
	d = dir;
	d.normalize();
}
