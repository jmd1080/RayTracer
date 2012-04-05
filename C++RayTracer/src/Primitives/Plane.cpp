/*
 * Plane.h
 *
 *  Created on: 5 Apr 2012
 *      Author: James Davies
 */

#include "GeometricObject.h"
#include "../Utilities/Normal.h"
#include "Plane.h"

Plane::Plane(void):
	GeometricObject(),
	n(Normal()),
	p(Point3D())
{}


Plane::Plane(Normal norm, Point3D point):
	GeometricObject(),
	n(norm),
	p(point)
{
	n.normalize();
}

void
Plane::set_normal(const Normal& norm)
{
	n = norm;
	n.normalize();
}

Plane::Plane(const Plane& plane):
	GeometricObject(),
	n(plane.n)
{}

Plane&
Plane::operator= (const Plane& rhs)
{
	n = rhs.n;
	p = rhs.p;

		return (*this);
}

Plane*
Plane::clone(void) const {
	return (new Plane(*this));
}

bool
Plane::hit(const Ray& ray, double& t, ShadeRec& s) const
{
	// find intersection point using formula from http://en.wikipedia.org/wiki/Line-plane_intersection
	float d = ((p - ray.o) * n) / (ray.d * n);

	// if less than 0 return as ray intersects behind camera
	if (d < 0)
		return false;

	t = d;
	s.normal = n;
	s.local_hit_point = ray.o + d * ray.d;
	return true;
}
