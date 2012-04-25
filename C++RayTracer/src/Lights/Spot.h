/*
 * Spot.h
 *
 *  Created on: 7 Apr 2012
 *      Author: James Davies
 */

#ifndef _Spot_
#define _Spot_

// This file contains the declaration of the class Sphere

#include "Light.h"

//-------------------------------------------------------------------------------- class Spot

class Spot: public Light {

	public:

		Spot(void);   								// Default constructor

		Spot(Point3D pnt, RGBColor In, Vector3D din, float arcin);				// Constructor

		Spot(const Spot& Spot); 		// Copy constructor

		Spot& 										// assignment operator
		operator= (const Spot& rhs);

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
		Vector3D	d;				// direction of the light
		float		arc;				// the arc of the light
};

#endif
