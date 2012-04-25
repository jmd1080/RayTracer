/*
 * Parser.cpp
 *
 *  Created on: 20 Apr 2012
 *      Author: James Davies
 */

#include "Parser.h"
#include <string>
#include "../Material/Material.h"

// primitives

#include "../Primitives/Sphere.h"
#include "../Primitives/Plane.h"
#include "../Primitives/Triangle.h"
#include "../Primitives/CSG.h"

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
#include "../Lights/Spot.h"

#include "../Tracers/RayCast.h"

#include "../Material/Material.h"

using namespace std;


Sphere*
Parser::ParseSphere(json_value *val)
{
	double x = 0, y = 0, z = 0;
	double rad = 0;
	json_value *v = val->first_child;
	string material = "default";
	while (v != NULL)
	{
		string n = v->name;
		if (n == "x")
			x = v->float_value;
		else if (n == "y")
			y = v->float_value;
		else if (n == "z")
			z = v->float_value;
		else if (n == "rad")
			rad = v->float_value;
		else if (n == "material")
			material = v->string_value;

		v = v->next_sibling;
	}
	Sphere *s = new Sphere(Point3D(x,y,z),rad);
	s->set_material_ptr(materials[material]);
	return s;
}


Triangle*
Parser::ParseTriangle(json_value *val)
{
	Point3D a = Point3D();
	Point3D b = Point3D();
	Point3D c = Point3D();
	json_value *v = val->first_child;
	string material = "default";

	while (v != NULL)
	{
		string n = v->name;
		if (n == "a_x")
			a.x = v->float_value;
		else if (n == "a_y")
			a.y = v->float_value;
		else if (n == "a_z")
			a.z = v->float_value;
		else if (n == "b_x")
			b.x = v->float_value;
		else if (n == "b_y")
			b.y = v->float_value;
		else if (n == "b_z")
			b.z = v->float_value;
		else if (n == "c_x")
			c.x = v->float_value;
		else if (n == "c_y")
			c.y = v->float_value;
		else if (n == "c_z")
			c.z = v->float_value;
		else if (n == "material")
			material = v->string_value;

		v = v->next_sibling;
	}
	Triangle *t = new Triangle(a,b,c);
	t->set_material_ptr(materials[material]);

	return t;
}

Plane*
Parser::ParsePlane (json_value *val)
{
	Normal norm = Normal();
	Point3D pnt = Point3D();
	string material = "default";

	json_value *v = val->first_child;
	while (v != NULL)
	{
		string n = v->name;
		if (n == "x")
			pnt.x = v->float_value;
		else if (n == "y")
			pnt.y = v->float_value;
		else if (n == "z")
			pnt.z = v->float_value;
		else if (n == "normx")
			norm.x = v->float_value;
		else if (n == "normy")
			norm.y = v->float_value;
		else if (n == "normz")
			norm.z = v->float_value;
		else if (n == "material")
			material = v->string_value;

		v = v->next_sibling;
	}
	Plane *p = new Plane(norm, pnt);
	p->set_material_ptr(materials[material]);

	return p;
}

CSG*
Parser::ParseCSG (json_value *val, string mode)
{
	GeometricObject *a = NULL;
	GeometricObject *b = NULL;

	json_value *v = val->first_child;
	a = getObject(v);
	b = getObject(v->next_sibling);

	int m = -1;
	if (mode == "Union")
		m = UNION;
	else if (mode == "Subtraction")
		m = SUBTRACTION;
	else if (mode == "Intersection")
		m = INTERSECTION;

	CSG *csg = new CSG(a,b,m);

	return csg;
}

void
Parser::ParsePointLight (json_value *val)
{
	RGBColor col = RGBColor();
	Point3D pnt = Point3D();

	json_value *v = val->first_child;
	while (v != NULL)
	{
		string n = v->name;
		if (n == "pnt_x")
			pnt.x = v->float_value;
		else if (n == "pnt_y")
			pnt.y = v->float_value;
		else if (n == "pnt_z")
			pnt.z = v->float_value;
		else if (n == "r")
			col.r = v->float_value/255;
		else if (n == "g")
			col.g = v->float_value/255;
		else if (n == "b")
			col.b = v->float_value/255;

		v = v->next_sibling;
	}
	Light *l = new Point(pnt,col);
	l = new Spot(pnt,col, Vector3D(1,0,0),0.5);

	w->add_light(l);
}

void
Parser::ParseDirectionalLight (json_value *val)
{
	RGBColor col = RGBColor();
	Vector3D dir = Vector3D();

	json_value *v = val->first_child;
	while (v != NULL)
	{
		string n = v->name;
		if (n == "dir_x")
			dir.x = v->float_value;
		else if (n == "dir_y")
			dir.y = v->float_value;
		else if (n == "dir_z")
			dir.z = v->float_value;
		else if (n == "r")
			col.r = v->float_value/255;
		else if (n == "g")
			col.g = v->float_value/255;
		else if (n == "b")
			col.b = v->float_value/255;

		v = v->next_sibling;
	}
	Light *l = new Directional(dir,col);

	w->add_light(l);
}

GeometricObject*
Parser::getObject (json_value *val)
{
	Material *default_material = new Material();
	default_material->set_color(white);
	string name = val->name;

	Point3D pnt = Point3D();
	if (name == "Sphere")
		return ParseSphere(val);
	else if (name == "Plane")
		return ParsePlane(val);
	else if (name == "Triangle")
		return ParseTriangle(val);
	else if (name == "Union" || name == "Intersection" || name == "Subtraction")
		return ParseCSG(val,name);

	return NULL;
}

void
Parser::ParseMaterial(json_value *val)
{
	RGBColor col = RGBColor();
	double kl = DEFAULT_KL;
	double kr = DEFAULT_KR;
	double ks = DEFAULT_KS;

	json_value *v = val->first_child;
	string material_name = "default";
	while (v != NULL)
	{
		string n = v->name;
		if (n == "r")
			col.r = v->float_value/255;
		else if (n == "g")
			col.g = v->float_value/255;
		else if (n == "b")
			col.b = v->float_value/255;
		else if (n == "kl")
			kl = v->float_value;
		else if (n == "kr")
			kr = v->float_value;
		else if (n == "ks")
			ks = v->float_value;
		else if (n == "name")
			material_name = v->string_value;

		v = v->next_sibling;
	}

	Material *m = new Material();

	m->set_kl(kl);
	m->set_kr(kr);
	m->set_ks(ks);

	m->set_color(col);

	if (material_name != "default")
		materials[material_name] = m;
	else
		fprintf(stderr,"Error: Material not named");
}

void
Parser::ParseCamera(json_value *val)
{
	Vector3D camDir = Vector3D();
	Point3D camPos = Point3D();
	float camRoll = 0;
	float zoom = 1;

	int sampleRate = 1;
	int vres = 0;
	int hres = 0;

	json_value *v = val->first_child;
	while (v != NULL)
	{
		string n = v->name;
		if (n == "dir_x")
			camDir.x = v->float_value;
		else if (n == "dir_y")
			camDir.y = v->float_value;
		else if (n == "dir_z")
			camDir.z = v->float_value;
		else if (n == "pos_x")
			camPos.x = v->float_value;
		else if (n == "pos_y")
			camPos.y = v->float_value;
		else if (n == "pos_z")
			camPos.z = v->float_value;
		else if (n == "samples")
			sampleRate = v->int_value;
		else if (n == "roll")
			camRoll = PI*v->float_value/180;
		else if (n == "vres")
			vres = v->int_value;
		else if (n == "hres")
			hres = v->int_value;
		else if (n == "zoom")
			zoom = v->float_value;

		v = v->next_sibling;
	}

	p->set_camera_roll(camRoll);
	p->set_sample_rate(1);
	p->set_camera_position(camPos);
	p->set_camera_dir(camDir);
	p->set_sample_rate(sampleRate);
	p->set_hres(hres);
	p->set_vres(vres);
	p->set_zoom(zoom);
}

void
Parser::ParseData(json_value *val)
{
	json_value *v = val->first_child;

	while (v != NULL)
	{
		if (!strcmp(v->name,"Material"))
		{
			ParseMaterial(v);
		}
		else if (!strcmp(v->name,"Camera"))
		{
			ParseCamera(v);
		}
		else if (!strcmp(v->name,"Directional-Light"))
		{
			ParseDirectionalLight(v);
		}
		else if (!strcmp(v->name,"Point-Light"))
		{
			ParsePointLight(v);
		}
		else
		{
			GeometricObject* g = getObject(v);
			if (g == NULL)
			{
				fprintf(stderr,"Error: Invalid object %s\n",v->name);
				exit(0);
			}
			w->add_object(g);
		}
		v = v->next_sibling;
	}
}

Parser::Parser(World *world, Pinhole *pin):
		w(world),
		p(pin),
		materials(TStrMatMap())
{
	materials["default"] = new Material();
	materials["default"]->set_color(white);
}

