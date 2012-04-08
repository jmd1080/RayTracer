// this file contains the definition of the World class

#include "World.h"
#include "../Utilities/Constants.h"

// primitives

#include "../Primitives/Sphere.h"
#include "../Primitives/Plane.h"
#include "../Primitives/Triangle.h"

// utilities

#include "../Utilities/Vector3D.h"
#include "../Utilities/Point3D.h"
#include "../Utilities/Normal.h"
#include "../Utilities/ShadeRec.h"
#include "../Utilities/Maths.h"
#include "../Utilities/RGBColor.h"

// lights

#include "../Lights/Directional.h"
#include "../Lights/Point.h"
#include "../Tracers/RayCast.h"

#include "../Material/Material.h"

#include <opencv/cv.h>
#include <opencv/highgui.h>

// -------------------------------------------------------------------- default constructor

// If no file is given create a default world with two spheres

World::World(void)
:  	background_color(black),
   	tracer_ptr(new RayCast(this)),
   	ambient(RGBColor(0.1)),
   	vp()
{
	img = cvCreateImage(cvSize(vp.vres,vp.hres), 8, 3);

	printf("Making sample world materials\n");

	Material *m1 = new Material();
	Material *m2 = new Material();
	Material *m3 = new Material();
	Material *m4 = new Material();
	Material *m5 = new Material();

	m5->set_color(RGBColor(0.5,0,0.5));
	m5->set_kr(0.5);

	m1->set_color(RGBColor(red));//1,0.01,0.01));
	//m1->set_kr(0.1);
	//m2->set_opacity(0);
	m2->set_color(white);
	m4->set_color(white);
	m4->set_kr(0.5);
	m2->set_kr(0.5);
	m3->set_color(white);//RGBColor(0.7,0.01,0.7));
	//background_color= RGBColor(1,1,0.01);

	Light *l2 = new Directional(Vector3D(-1,1,1),RGBColor(0.3,0.3,0.3));
	add_light(l2);
	Light *l3 = new Directional(Vector3D(-1,1,-1),RGBColor(0.3,0.3,0.3));
		add_light(l3);

	Light *l1 = new Point(Point3D(-200,0,0),RGBColor(0.5,0.5,0.5));

	//add_light(l1);

	printf("Making sample world\n");

	Sphere *s1 = new Sphere(Point3D(-50,-50,-100),50);
	s1->set_material_ptr(m1);
	Sphere *s2 = new Sphere(Point3D(50,50,-200),50);
	s2->set_material(2);
	s2->set_material_ptr(m5);
	Sphere *s3 = new Sphere(Point3D(0,0,-300),50);
	s3->set_material(2);
	s3->set_material_ptr(m2);

	Plane *p1 = new Plane(Normal(-1,0,0), Point3D(200,0,0));
	p1->set_material_ptr(m4);

	Triangle *t1 = new Triangle(Point3D(50,-50,-150),Point3D(50,80,-200),Point3D(0,0,-300));
	t1->set_material_ptr(m3);

	// CSG ************************

	Sphere *CSG1 = new Sphere(Point3D(50,25,-500),50);
	CSG1->set_material_ptr(m1);
	Sphere *CSG2 = new Sphere(Point3D(50,-25,-500),50);
	CSG2->set_material_ptr(m3);

	add_object(CSG1);
	add_object(CSG2);

	// ****************************

	/*add_object(s1);
	add_object(s2);
	add_object(t1);
	add_object(s3);*/
	add_object(p1);
}



//------------------------------------------------------------------ destructor

World::~World(void) {	
	delete_objects();	
	delete_lights();
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
	sr.ray = ray;

	for (int j = 0; j < num_objects; j++)
		if (objects[j]->hit(ray, t, sr)) {
			sr.inv_opacity *= (1-objects[j]->get_material_ptr()->get_opacity());
			if (t < tmin) {
				sr.hit_an_object	= true;
				tmin 				= t;
				sr.material = objects[j]->get_material();
				sr.material_ptr     = objects[j]->get_material_ptr(); // TODO fix issues with material
				sr.hit_point 		= ray.o + t * ray.d;
				normal 				= sr.normal;
				local_hit_point	 	= sr.local_hit_point;
			}
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
	//IplImage *display = cvCreateImage(cvSize(vres,hres), 8, 3);

	//cvCircle(display, cvPoint(hres/2,vres/2), hres/2, cvScalar(255,255,255),-1);

	//cvShowImage("Result",display);

	for (int r = 0; r < vres; r++)			// up
	{
		for (int c = 0; c < hres; c++) {	// across

			// Create ray for this pixel

			ray.o = Point3D(s * (c - hres / 2.0 + 0.5), s * (r - vres / 2.0 + 0.5), zw);
			//ShadeRec sr = hit_objects(ray);

			pixel_color = tracer_ptr->trace_ray(ray);
			/*CvScalar s = cvGet2D(img,c,r);
						s.val[0] = pixel_color.b*255;
						s.val[1] = pixel_color.g*255;
						s.val[2] = pixel_color.r*255;

						cvSet2D(img,c,r,s);*/
			draw_pixel(pixel_color, c, r);
		}	
	}
	display_image();
}  

//------------------------------------------------------------------ image related functions

void
World::draw_pixel(RGBColor pixel_color, int c, int r) const
{
	if (img == NULL)
		return;
	if (c >= img->width || r >= img->height)
		return;
	CvScalar s = cvGet2D(img,c,r);
	s.val[0] = pixel_color.b*255;
	s.val[1] = pixel_color.g*255;
	s.val[2] = pixel_color.r*255;

	cvSet2D(img,c,r,s);

}

void
World::display_image(void) const
{
	cvShowImage("Image",img);
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

// Same for lights

void
World::delete_lights(void) {
	int num_lights = lights.size();

	for (int j = 0; j < num_lights; j++) {
		delete lights[j];
		lights[j] = NULL;
	}

	lights.erase (lights.begin(), lights.end());
}

