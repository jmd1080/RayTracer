// this file contains the definition of the World class

#include "World.h"
#include "../Utilities/Constants.h"

// geometric objects

#include "../Primitives/Plane.h"
#include "../Primitives/Sphere.h"

// utilities

#include "../Utilities/Vector3D.h"
#include "../Utilities/Point3D.h"
#include "../Utilities/Normal.h"
#include "../Utilities/ShadeRec.h"
#include "../Utilities/Maths.h"

#include "../Tracers/RayCast.h"

#include <opencv/cv.h>
#include <opencv/highgui.h>

// -------------------------------------------------------------------- default constructor

// If no file is given create a default world with two spheres

World::World(void)
	:  	background_color(black),
		tracer_ptr(new RayCast(this)),
		ambient(10),
		vp()
{
	printf("Making sample world\n");
	Sphere *s1 = new Sphere(Point3D(-50,-50,0),50);
	s1->set_material(2);
	Sphere *s2 = new Sphere(Point3D(50,50,-40),50);
	s2->set_material(2);
	Sphere *s3 = new Sphere(Point3D(0,0,-20),50);
	s3->set_material(1);
	add_object(s1);
	add_object(s2);
	add_object(s3);
}



//------------------------------------------------------------------ destructor

World::~World(void) {	
	delete_objects();	
}



// ----------------------------------------------------------------------------- hit_objects

ShadeRec
World::hit_objects(const Ray& ray) {

	// ShadeRec
	ShadeRec	sr(*this);
	double		t;
	Normal normal;
	Point3D local_hit_point;
	float		tmin 			= kHugeValue;
	int 		num_objects 	= objects.size();

	for (int j = 0; j < num_objects; j++)
		if (objects[j]->hit(ray, t, sr) && (t < tmin)) {
			sr.hit_an_object	= true;
			tmin 				= t;
			sr.material = objects[j]->get_material();
			//sr.material_ptr     = objects[j]->get_material(); // TODO fix issues with material
			sr.hit_point 		= ray.o + t * ray.d;
			normal 				= sr.normal;
			local_hit_point	 	= sr.local_hit_point;
		}

	if(sr.hit_an_object) {
		sr.t = tmin;
		sr.normal = normal;
		sr.local_hit_point = local_hit_point;
	}
	//printf("%d",sr.material);
	return(sr);
}

//------------------------------------------------------------------ render_scene

// This uses orthographic viewing along the zw axis

void 												
World::render_scene(void) const {

	RGBColor	pixel_color;	 	
	Ray			ray;
	int 		hres 	= vp.hres;
	int 		vres 	= vp.vres;
	float		s		= vp.s;
	float		zw		= 100.0;				// hardwired in

	ray.d = Vector3D(0, 0, -1);
	

	// Create image
	IplImage *display = cvCreateImage(cvSize(vres,hres), 8, 3);

	//cvCircle(display, cvPoint(hres/2,vres/2), hres/2, cvScalar(255,255,255),-1);

	//cvShowImage("Result",display);

	for (int r = 0; r < vres; r++)			// up
	{
		for (int c = 0; c < hres; c++) {	// across

			// Create ray for this pixel

			ray.o = Point3D(s * (c - hres / 2.0 + 0.5), s * (r - vres / 2.0 + 0.5), zw);
			//ShadeRec sr = hit_objects(ray);

			pixel_color = tracer_ptr->trace_ray(ray);

			CvScalar s = cvGet2D(display,c,r);
			s.val[0] = pixel_color.b*255;
			s.val[1] = pixel_color.g*255;
			s.val[2] = pixel_color.r*255;

			cvSet2D(display,c,r,s);

			//display_pixel(r, c, pixel_color);
		}	
	}

	cvShowImage("Image",display);
	cvWaitKey(0);
}  



//------------------------------------------------------------------ delete_objects

// Deletes the objects in the objects array, and erases the array.
// The objects array still exists, because it's an automatic variable, but it's empty 

void
World::delete_objects(void) {
	int num_objects = objects.size();
	
	for (int j = 0; j < num_objects; j++) {
		delete objects[j];
		objects[j] = NULL;
	}	
	
	objects.erase (objects.begin(), objects.end());
}

