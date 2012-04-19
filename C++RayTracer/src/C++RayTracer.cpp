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

using namespace std;

void addObject (json_value *val)
{
	string name = val->name;

	if (name == "Sphere")
	{
		printf("PARSE Sphere\n");
	}
	else if (name == "Plane")
	{
		printf("PARSE Plane\n");
	}
	else if (name == "Triangle")
	{
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

	if (root == NULL)
	{
		fprintf(stderr,"Error: Could not parse file\n");
		fprintf(stderr,"Error: %d,%s:%s\n",errorLine,errorPos,errorDesc);
		return 0;
	}
	json_value *v = root->first_child;
	while (v != NULL)
	{
		printf("Adding a %s\n",v->name);
		addObject(v);
		v = v->next_sibling;
	}



	//w.render_scene();
	Point3D center = Point3D(50,0,-500);
	Pinhole p = Pinhole();
	Point3D camPos = Point3D(0,0,-900);
	p.set_camera_roll(PI);
	p.set_sample_rate(1);
	p.set_camera_position(camPos);
	p.set_camera_dir(center - camPos);
	p.render_scene(w);
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
