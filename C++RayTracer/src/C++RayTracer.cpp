//============================================================================
// Name        : C++RayTracer.cpp
// Author      : James Davies
// Version     : 1
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "cstdlib"
#include "cmath"
#include <opencv/highgui.h>
#include "World/World.h"
#include "Camera/Pinhole.h"
#include "vjson/json.h"
#include <iostream>
#include <fstream>
#include <string>

#include "Primitives/Sphere.h"
#include "Primitives/Plane.h"
#include "Primitives/Triangle.h"
#include "Primitives/CSG.h"
#include "Material/Material.h"

#include "Parser/Parser.h"

using namespace std;

void addObject (json_value *val, World* w)
{
	Material *default_material = new Material();
	default_material->set_color(white);
	string name = val->name;
	double x = 0;
	double y = 0;
	double z = 0;
	Point3D pnt = Point3D();
	if (name == "Sphere")
	{
		double rad = 0;
		json_value *v = val->first_child;
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

			v = v->next_sibling;
		}
		Sphere *s = new Sphere(Point3D(x,y,z),rad);
		s->set_material_ptr(default_material);
		w->add_object(s);

		printf("PARSE Sphere %f, %f, %f, %f\n", x, y, z, rad);
	}
	else if (name == "Plane")
	{
		double normx = 0;
		double normy = 0;
		double normz = 0;
		json_value *v = val->first_child;
		while (v != NULL)
		{
			string n = v->name;
			if (n == "x")
				x = v->float_value;
			else if (n == "y")
				y = v->float_value;
			else if (n == "z")
				z = v->float_value;
			else if (n == "normx")
				normx = v->float_value;
			else if (n == "normy")
				normy = v->float_value;
			else if (n == "normz")
				normz = v->float_value;

			v = v->next_sibling;
		}
		Plane *p = new Plane(Normal(normx,normy,normz), Point3D(x,y,z));
		p->set_material_ptr(default_material);
		w->add_object(p);

		printf("PARSE Plane %f, %f, %f\n", x, y, z);
	}
	else if (name == "Triangle")
	{
		Point3D a = Point3D();
		Point3D b = Point3D();
		Point3D c = Point3D();
		json_value *v = val->first_child;
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

			v = v->next_sibling;
		}
		Triangle *t = new Triangle(a,b,c);
		t->set_material_ptr(default_material);
		w->add_object(t);
		printf("PARSE Triangle\n");
	}
	else if (name == "Material")
	{
		printf("PARSE Material\n");
	}
}

int main(int argc, char* argv[]) {
	cout << "Ray Tracer" << endl;

	string line;
	string in;
	ifstream myfile ("hello.json");

	if (myfile.is_open())
	{
		while ( myfile.good() )
		{
			getline (myfile,line);
			in.append(line+"\n");
		}
		myfile.close();
	}
	else cout << "Unable to open file";

	char source[in.length()];

	strcpy(source,in.c_str());

	char *errorPos = 0;
	char *errorDesc = 0;
	int errorLine = 0;
	block_allocator allocator(1 << 10); // 1 KB per block

	json_value *root = json_parse(source, &errorPos, &errorDesc, &errorLine, &allocator);

	World *w = new World();
	Pinhole *p = new Pinhole();

	Parser *parser = new Parser(w,p);

	if (root == NULL)
	{
		fprintf(stderr,"Error: Could not parse file\n");
		fprintf(stderr,"Error: %d,%s:%s\n",errorLine,errorPos,errorDesc);
		return 0;
	}

	parser->ParseData(root);

	p->render_scene(w);


	/*
	 * 	int total = 20;
	 *
	for (int i = 0; i < total; i++)
	{
		Pinhole p = Pinhole();
		Point3D camPos = Point3D(0,600*cos(2*PI*i/total),-600*cos(2*PI*i/total));
		p.set_camera_position(camPos);
		p.set_camera_dir(center - camPos);
		//p.set_camera_roll(-i*PI/total);
		p.render_scene(w);
	}*/

	return 0;
}
