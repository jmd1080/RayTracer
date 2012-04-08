#ifndef __CSG__
#define __CSG__

#include "GeometricObject.h"

const int UNION = 0;
const int SUBTRACTION = 1;
const int INTERSECTION = 2;

class CSG: public GeometricObject {

	public:

		CSG(void);

		CSG(GeometricObject *aIn, GeometricObject *bIn, int opIn);

		CSG(const CSG& CSG);

		bool
		union_hit(const Ray& ray, double& tmin, ShadeRec& sr) const;

		bool
		sub_hit(const Ray& ray, double& tmin, ShadeRec& sr) const;

		bool
		intersect_hit(const Ray& ray, double& tmin, ShadeRec& sr) const;

		virtual CSG*								// virtual copy constructor
		clone(void) const;

		CSG&
		operator= (const CSG& CSG);

		virtual bool
		hit(const Ray& ray, double& t, ShadeRec& s) const;

	private:

		GeometricObject* 	a;
		GeometricObject*	b;
		int					op; // The operation on the two objects
};


#endif

