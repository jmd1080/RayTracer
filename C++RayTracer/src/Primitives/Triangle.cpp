/*
 * Triangle.h
 *
 *  Created on: 5 Apr 2012
 *      Author: James Davies
 */

#include "GeometricObject.h"
#include "../Utilities/Normal.h"
#include "../Utilities/Constants.h"
#include "Triangle.h"
#include <stdio.h>
#include "../Material/Material.h"

Triangle::Triangle(void):
	GeometricObject(),
	a(Point3D()),
	b(Point3D()),
	c(Point3D()),
	n(Normal())
{}


Triangle::Triangle(Point3D ai, Point3D bi, Point3D ci):
	GeometricObject(),
	a(ai),
	b(bi),
	c(ci)
{
	update_normal();
}

Triangle::Triangle(const Triangle& triangle):
	GeometricObject(),
	a(triangle.a),
	b(triangle.b),
	c(triangle.c)
{
	update_normal();
}

void Triangle::update_normal()
{
	n = Normal((b - a) ^ (c - a));
	n.normalize();
	printf("%f,%f,%f\n",n.x,n.y,n.z);
}

Triangle&
Triangle::operator= (const Triangle& rhs)
{
	a = rhs.a;
	b = rhs.b;
	c = rhs.c;
	update_normal();
	return (*this);
}

Triangle*
Triangle::clone(void) const {
	return (new Triangle(*this));
}

bool
Triangle::hit(const Ray& ray, double& t, double& tmax, ShadeRec& s) const
{
	// Find intersection, source p.362 Ray Tracing from the ground up
	// TODO remove repeated calculations
	s.material_ptr = material_ptr;

	// find intersection point using formula from http://en.wikipedia.org/wiki/Line-plane_intersection
	float dist = ((a - ray.o) * n) / (ray.d * n);

	// if less than 0 return as ray intersects behind camera
	if (dist < kEpsilon)
		return false;

	float a1 = a.x - b.x, b1 = a.x - c.x, c1 = ray.d.x, d1 = a.x - ray.o.x,
		  e1 = a.y - b.y, f1 = a.y - c.y, g1 = ray.d.y, h1 = a.y - ray.o.y,
		  i1 = a.z - b.z, j1 = a.z - c.z, k1 = ray.d.z, l1 = a.z - ray.o.z;

	float div = 1/(a1*(f1*k1 + g1*j1) + b1*(g1*i1 - e1*k1) + c1*(e1*j1 - f1*i1));

	float beta = (d1 *(f1*k1 - g1*j1) + b1*(g1*l1 - h1*k1) + c1*(h1*j1 - f1*l1)) * div;

	if (beta < -kEpsilon)
		return false;

	float gamma = (a1*(h1*k1 - g1*l1) + d1*(g1*i1 - e1*k1) + c1*(e1*l1 - h1*i1)) * div;

	if (gamma < -kEpsilon)
		return false;

	if (beta + gamma > 1 + kEpsilon)
		return false;

	t = dist;
	s.normal = n;
	s.local_hit_point = ray.o + t * ray.d;
	s.hit_point = s.local_hit_point;
	s.normal_max   = -1*n;
	s.max_hit_point = s.local_hit_point;

	return true;
}
