#ifndef __DIRECTIONAL__
#define __DIRECTIONAL__

// This file contains the declaration of the class Sphere

#include "Light.h"

//-------------------------------------------------------------------------------- class Directional

class Directional: public Light {

	public:

		Directional(void);   								// Default constructor

		Directional(Vector3D dir, float In);				// Constructor

		Directional(const Directional& directional); 		// Copy constructor

		Directional& 										// assignment operator
		operator= (const Directional& rhs);

		// Set the intensity
	    virtual void
		set_intensity(float In);

		virtual float
		get_intensity(ShadeRec& sr) const;

		virtual float
		get_rv(ShadeRec& sr);

		void
		set_dir(const Vector3D& dir);

	private:

		float		Il;					// intensity of the light
		Vector3D 	d;   				// direction of the light
};

#endif
