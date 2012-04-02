#ifndef __WORLD__
#define __WORLD__

// Based on World.h from Skeleton RayTracer TODO ATTRIBUTIONS

#include "../Primitives/Plane.h"
#include "../Primitives/Sphere.h"
#include "../Utilities/RGBColor.h"
#include "../Tracers/Tracer.h"
#include "ViewPlane.h"

#include <vector>

using namespace std;


class World {
	public:

		ViewPlane					vp;
		RGBColor					background_color;
		vector<GeometricObject*>	objects;
		Tracer*						tracer_ptr;

		int ambient;//TODO

	public:

		World(void);

		~World();

		void
		add_object(GeometricObject* object_ptr);

		void
		set_ambient_light(int light);

		void
		build(void);

		void
		render_scene(void) const;

		ShadeRec
		hit_objects(const Ray& ray);


	private:

		void
		delete_objects(void);
};


// ------------------------------------------------------------------ add_object

inline void
World::add_object(GeometricObject* object_ptr) {
	objects.push_back(object_ptr);
}



// ------------------------------------------------------------------ set_ambient_light

inline void
World::set_ambient_light(int light) {
	ambient = light;
}

#endif
