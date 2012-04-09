// This file contains the definition of the class sphere

#include "Sphere.h"
#include "math.h"
#include <stdio.h>

const double Sphere::kEpsilon = 0.001;

// ---------------------------------------------------------------- default constructor

Sphere::Sphere(void)
: 	GeometricObject(),
  	center(0.0),
  	radius(1.0)
{}


// ---------------------------------------------------------------- constructor

Sphere::Sphere(Point3D c, double r)
: 	GeometricObject(),
  	center(c),
  	radius(r)
{}


// ---------------------------------------------------------------- clone

Sphere*
Sphere::clone(void) const {
	return (new Sphere(*this));
}


// ---------------------------------------------------------------- copy constructor

Sphere::Sphere (const Sphere& sphere)
: 	GeometricObject(sphere),
  	center(sphere.center),
  	radius(sphere.radius)
{}



// ---------------------------------------------------------------- assignment operator

Sphere&
Sphere::operator= (const Sphere& rhs)
{
	if (this == &rhs)
		return (*this);

	GeometricObject::operator= (rhs);

	center 	= rhs.center;
	radius	= rhs.radius;

	return (*this);
}


// ---------------------------------------------------------------- destructor

Sphere::~Sphere(void) {}


//---------------------------------------------------------------- hit

bool
Sphere::hit(const Ray& ray, double& tmin, double& tmax, ShadeRec& sr) const {
	double t;
	Vector3D	temp 	= ray.o - center;
	double 		a 		= ray.d * ray.d;
	double 		b 		= 2.0 * temp * ray.d;
	double 		c 		= temp * temp - radius * radius;
	double 		disc	= b * b - 4.0 * a * c;

	sr.material_ptr = material_ptr;

	if (disc < 0.0)
		return(false);
	else {
		double e = sqrt(disc);
		double denom = 2.0 * a;
		t = (-b - e) / denom;    // smaller root
		if (t < -kEpsilon) {
			tmax = t;
			sr.normal_max   = (temp + t * ray.d) / radius;
			sr.max_hit_point = ray.o + t * ray.d;
		}

		if (t > kEpsilon) {
			tmin = t;
			sr.normal 	 = (temp + t * ray.d) / radius;
			sr.local_hit_point = ray.o + t * ray.d;
			t = (-b + e) / denom;    // larger root
			tmax = t;
			sr.normal_max   = (temp + t * ray.d) / radius;
			sr.max_hit_point = ray.o + t * ray.d;
			//sr.material_ptr = material_ptr;
			return true;
		}
		t = (-b + e) / denom;    // larger root

		if (t > kEpsilon) {
			tmin = t;
			sr.normal   = (temp + t * ray.d) / radius;
			sr.local_hit_point = ray.o + t * ray.d;
			return true;
		}
	}

	return (false);
}







