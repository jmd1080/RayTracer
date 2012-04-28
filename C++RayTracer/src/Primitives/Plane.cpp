/*
 * Plane.h
 *
 *  Created on: 5 Apr 2012
 *      Author: James Davies
 */

#include "GeometricObject.h"
#include "../Utilities/Normal.h"
#include "../Utilities/Constants.h"
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
	n(plane.n),
	p(plane.p)
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
Plane::hit(const Ray& ray, double& t, double& tmax, ShadeRec& s) const
{
	s.material_ptr = material_ptr;
	// find intersection point using formula from http://en.wikipedia.org/wiki/Line-plane_intersection
	float d = ((p - ray.o) * n) / (ray.d * n);

	if (d < 4*kEpsilon)
		return false;

	t = d;
	s.normal = n;

	s.local_hit_point = ray.o + d * ray.d;
	s.normal_max   = -1*s.normal;
	s.max_hit_point = s.local_hit_point;

	// if intersecting with the inverse side
	if(ray.d*n > kEpsilon)
	{
		s.normal = -1*n;
		s.normal_max   = n;
	}
	return true;
}
