/*
 * Parser.h
 *
 *  Created on: 20 Apr 2012
 *      Author: James Davies
 */

#ifndef _PARSER_
#define _PARSER_

#include <map>
#include <string>
#include "../Material/Material.h"
#include <hash_map>
#include "../vjson/json.h"

// primitives

#include "../Primitives/Sphere.h"
#include "../Primitives/Plane.h"
#include "../Primitives/Triangle.h"
#include "../Primitives/CSG.h"

#include "../Camera/Pinhole.h"

typedef std::map<std::string, Material*> TStrMatMap;

class Parser {
	public:
		Parser(World *world, Pinhole *p);

		void
		ParseData(json_value *val);

	private:
		GeometricObject
		*getObject (json_value *val);

		Sphere*
		ParseSphere(json_value *val);

		CSG*
		ParseCSG (json_value *val, string mode);

		Triangle*
		ParseTriangle(json_value *val);

		Plane*
		ParsePlane(json_value *val);

		void
		ParsePointLight(json_value *val);

		void
		ParseDirectionalLight(json_value *val);

		void
		ParseSpotLight(json_value *val);

		void
		ParseMaterial(json_value *val);

		void
		ParseCamera(json_value *val);

		World *w; // The world the parser adds objects to
		Pinhole *p; // The camera the world will be viewed with

		TStrMatMap materials;

};

#endif
