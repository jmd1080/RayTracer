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

	return 0;
}
