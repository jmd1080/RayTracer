// This file contains the definition of the class RGBColor

#include <math.h>

#include "RGBColor.h"
#include <stdio.h>

// -------------------------------------------------------- default constructor

RGBColor::RGBColor(void)
: r(0.0), g(0.0), b(0.0)
{}


// -------------------------------------------------------- constructor

RGBColor::RGBColor(float c)
: r(c), g(c), b(c)
{
	cap();
}


// -------------------------------------------------------- constructor

RGBColor::RGBColor(float _r, float _g, float _b)	
: r(_r), g(_g), b(_b)
{
	cap();
}


// -------------------------------------------------------- copy constructor

RGBColor::RGBColor(const RGBColor& c)
: r(c.r), g(c.g), b(c.b)
{
	cap();
}


// -------------------------------------------------------- destructor

RGBColor::~RGBColor(void)		
{}


// --------------------------------------------------------assignment operator

RGBColor& 											
RGBColor::operator= (const RGBColor& rhs) {
	if (this == &rhs)
		return (*this);

	r = rhs.r; g = rhs.g; b = rhs.b;

	return (*this);
}

void
RGBColor::cap() {
	if (r > 1.0)
		r = 1.0;
	if (g > 1.0)
		g = 1.0;
	if (b > 1.0)
		b = 1.0;
}


// -------------------------------------------------------- powc
// raise each component to the specified power
// used for color filtering in Chapter 28

RGBColor
RGBColor::powc(float p) const {
	return (RGBColor(pow(r, p), pow(g, p), pow(b, p)));
}

