#ifndef __PLANE__
#define __PLANE__

#include "GeometricObject.h"

class Plane: public GeometricObject {

	public:

		Plane(void);

		Plane(Normal norm, Point3D point);

		Plane(const Plane& plane);

		virtual Plane*								// virtual copy constructor
		clone(void) const;

		Plane&
		operator= (const Plane& plane);

		void
		set_normal(const Normal& norm);

		void
		set_point(const Point3D& point);

		virtual bool
		hit(const Ray& ray, double& t, ShadeRec& s) const;

	private:

		Normal 		n;   			// Normal vector to the plane
		Point3D		p;				// Point on the plane
};

inline void
Plane::set_point(const Point3D& point)
{
	p = point;
}


#endif

