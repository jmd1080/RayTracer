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

using namespace std;

int main() {
	cout << "Ray Tracer" << endl;
	World w = World();
	//w.render_scene();
	Point3D center = Point3D(50,0,-300);
	Pinhole p = Pinhole();
	Point3D camPos = Point3D(0,0,0);
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
