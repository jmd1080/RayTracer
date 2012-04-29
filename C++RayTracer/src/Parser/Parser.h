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
		// Returns the geometric object described by the given json data
		GeometricObject
		*getObject (json_value *val);

		// Returns the sphere described by the given json data
		Sphere*
		ParseSphere(json_value *val);

		/* Returns the CSG object described by the given json data,
		** string gives whether it is a UNION, INTERSECTION or SUBTRACTION operation */
		CSG*
		ParseCSG (json_value *val, string mode);

		// Returns the triangle described by the given json data
		Triangle*
		ParseTriangle(json_value *val);

		// Returns the plane described by the given json data
		Plane*
		ParsePlane(json_value *val);

		// Adds the point light described by the json data to the world
		void
		ParsePointLight(json_value *val);

		// Adds the directional light described by the json data to the world
		void
		ParseDirectionalLight(json_value *val);

		// Adds the spot light described by the json data to the world
		void
		ParseSpotLight(json_value *val);

		// Sets the ambient light of the world as described by the json data
		void
		ParseAmbientLight(json_value *val);

		// Adds the material described by the json data to the list of materials
		void
		ParseMaterial(json_value *val);

		// Adjusts the camera settings as described in the json data
		void
		ParseCamera(json_value *val);

		World *w; // The world the parser adds objects to
		Pinhole *p; // The camera the world will be viewed with

		TStrMatMap materials;

};

#endif
