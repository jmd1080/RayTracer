#ifndef __TRIANGLE__
#define __TRIANGLE__

#include "GeometricObject.h"

class Triangle: public GeometricObject {

	public:

		Triangle(void);

		Triangle(Point3D a, Point3D b, Point3D c);

		Triangle(const Triangle& triangle);

		virtual Triangle*								// virtual copy constructor
		clone(void) const;

		Triangle&
		operator= (const Triangle& triangle);

		void
		update_normal(void);

		void
		set_a(const Point3D& point);

		void
		set_b(const Point3D& point);

		void
		set_c(const Point3D& point);

		void
		set_points(const Point3D& ai, const Point3D& bi, const Point3D& ci);

		virtual bool
		hit(const Ray& ray, double& t, double& tmax,ShadeRec& s) const;

	private:

		Point3D a;
		Point3D b;
		Point3D c;
		Normal n; // pre-computed normal
};

inline void
Triangle::set_a(const Point3D& point)
{
	a = point;
	update_normal();
}

inline void
Triangle::set_b(const Point3D& point)
{
	b = point;
	update_normal();
}

inline void
Triangle::set_c(const Point3D& point)
{
	c = point;
	update_normal();
}

inline void
Triangle::set_points(const Point3D& ai, const Point3D& bi, const Point3D& ci)
{
	a = ai;
	b = bi;
	c = ci;
	update_normal();
}


#endif

