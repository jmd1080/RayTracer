//============================================================================
// Name        : C++RayTracer.cpp
// Author      : James Davies
// Version     : 1
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "cstdlib"
#include "cmath"
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include "World/World.h"
#include "Camera/Pinhole.h"

using namespace std;

int main() {
	cout << "Ray Tracer" << endl;
	World w = World();
	w.render_scene();
	Pinhole p = Pinhole();
	p.render_scene(w);
	return 0;
}
