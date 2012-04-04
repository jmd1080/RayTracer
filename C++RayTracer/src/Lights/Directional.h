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

		virtual float
		get_intensity(ShadeRec& sr) const;

		void
		set_dir(const Vector3D& dir);

	private:

		Vector3D 	d;   				// direction of the light
};



inline void
Directional::set_dir(const Vector3D& dir) {
	d = dir;
}

#endif
