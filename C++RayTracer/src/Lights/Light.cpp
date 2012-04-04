/*
 * Light.cpp
 *
 *  Created on: 4 Apr 2012
 *      Author: James Davies
 */

#include "Light.h"

// default constructor

Light::Light(void)
	: Il(0)
{}

Light::Light(float in)
	: Il(in)
{}



// ---------------------------------------------------------------------- copy constructor

Light::Light (const Light& light) {
	Il = light.Il;
}


// ---------------------------------------------------------------------- assignment operator

Light&
Light::operator= (const Light& rhs) {

	Il = rhs.Il;
	return (*this);
}


// ---------------------------------------------------------------- set_intensity

void
Light::set_intensity(float In) {
	Il = In;
}
