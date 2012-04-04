/*
 * Directional.cpp
 *
 *  Created on: 4 Apr 2012
 *      Author: jamie
 */

#include "Directional.h"

// Default constructor

Directional::Directional(void)
{

}

// Constructor

Directional::Directional(Vector3D dir, float In)
{

}

// Copy constructor

Directional::Directional(const Directional& directional)
{

}

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
return 1;
}
