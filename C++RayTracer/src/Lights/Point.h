/*
 * Point.h
 *
 *  Created on: 7 Apr 2012
 *      Author: James Davies
 */

#ifndef _POINT_
#define _POINT_

// This file contains the declaration of the class Sphere

#include "Light.h"

//-------------------------------------------------------------------------------- class Point

class Point: public Light {

	public:

		Point(void);   								// Default constructor

		Point(Point3D pnt, RGBColor In);				// Constructor

		Point(const Point& Point); 		// Copy constructor

		Point& 										// assignment operator
		operator= (const Point& rhs);

		// Set the intensity
	    virtual void
		set_intensity(RGBColor In);

		virtual RGBColor
		get_intensity(ShadeRec& sr) const;

		virtual float
		get_rv(ShadeRec& sr);

		void
		set_loc(const Point3D& pnt);

	private:

		RGBColor	cl;					// color of the light
		Point3D 	p;   				// location of the light
};

#endif
