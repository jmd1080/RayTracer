#ifndef __CSG__
#define __CSG__

#include "GeometricObject.h"

const int UNION = 0;
const int SUBTRACTION = 1;
const int INTERSECTION = 2;

class CSG: public GeometricObject {

	public:

		// Default constructor
		CSG(void);

		/* Constructor, takes two GeometricObject pointers as objects A and B and
		** int value describing if it is UNION SUBTRACTION or INTERSECTION */
		CSG(GeometricObject *aIn, GeometricObject *bIn, int opIn);

		CSG(const CSG& CSG);

		// Carries out hit method on union objects
		bool
		union_hit(const Ray& ray, double& tmin, double& tmax, ShadeRec& sr) const;

		// Carries out hit method on subtraction objects
		bool
		sub_hit(const Ray& ray, double& tmin, double& tmax, ShadeRec& sr) const;

		// Carries out hit method on intersection objects
		bool
		intersect_hit(const Ray& ray, double& tmin, double& tmax, ShadeRec& sr) const;

		virtual CSG*								// virtual copy constructor
		clone(void) const;

		CSG&
		operator= (const CSG& CSG);


		/* Takes a ray and returns if it hits the object
		** sets tmin to the distance of the first hit,
		** tmax to the distance of the last hit and
		** sets the values in the ShaderRec*/

		virtual bool
		hit(const Ray& ray, double& t, double& tmax, ShadeRec& s) const;

	private:

		GeometricObject* 	a;
		GeometricObject*	b;
		int					op; // The operation on the two objects
};


#endif

