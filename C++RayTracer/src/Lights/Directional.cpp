/*
 * Directional.cpp
 *
 *  Created on: 4 Apr 2012
 *      Author: jamie
 */

#include "Directional.h"

// Default constructor

Directional::Directional(void):
Light(),
d(Vector3D(0))
{}

// Constructor

Directional::Directional(Vector3D dir, float In):
		Light(In),
		d(dir)
{}

// Copy constructor

Directional::Directional(const Directional& directional):
		Light(directional),
		d(directional.d)
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
	return 0.5;
}

void
Directional::set_dir(const Vector3D& dir) {
	d = dir;
	d.normalize();
}
