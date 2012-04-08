#ifndef __SHADE_REC__
#define __SHADE_REC__

// this file contains the declaration of the class ShadeRec

#include <vector>

class Material;
class World;

// We need the following as #includes instead of forward class declarations,
// because we have the objects themselves, not pointers or references

#include "Point3D.h"
#include "Normal.h"
#include "Ray.h"
#include "RGBColor.h"

class ShadeRec {
	public:
	
		bool				hit_an_object;		// Did the ray hit an object?
		Material* 			material_ptr;		// Pointer to the nearest object's material
		int 				material;
		Point3D 			hit_point;			// World coordinates of intersection
		Point3D				local_hit_point;	// World coordinates of hit point on generic object (used for texture transformations)
		Point3D				max_hit_point;		// World coordinates of hit point at tmax (used for CSG)
		Normal				normal;				// Normal at hit point
		Ray					ray;				// Required for specular highlights and area lights
		int					depth;				// recursion depth
		float				t;					// ray parameter
		float				tmax;				// Used for CSG
		Normal				normal_max;
		World&				w;					// World reference
		RGBColor            color;
		double				inv_opacity;			// Used for transparency in shadows
				
		ShadeRec(World& wr);					// constructor
		
		ShadeRec(const ShadeRec& sr);			// copy constructor
};

#endif
