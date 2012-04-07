#ifndef __WORLD__
#define __WORLD__

// Based on World.h from Skeleton RayTracer TODO ATTRIBUTIONS

#include "../Primitives/Sphere.h"
#include "../Utilities/RGBColor.h"
#include "../Tracers/Tracer.h"
#include "../Lights/Light.h"
#include "ViewPlane.h"
#include <opencv/cv.h>

#include <vector>

using namespace std;


class World {
	public:

		ViewPlane					vp;						//Used for orthogonal plotting
		RGBColor					background_color;
		vector<GeometricObject*>	objects;
		vector<Light*>				lights;
		Tracer*						tracer_ptr;
		IplImage*					img;					//The output image of the world

		RGBColor					ambient;				//Ambient light

	public:

		World(void);

		~World();

		void
		add_object(GeometricObject* object_ptr);

		void
		add_light(Light* light_ptr);

		void
		set_ambient_light(int light);

		void
		build(void);

		void
		render_scene(void) const;

		ShadeRec
		hit_objects(const Ray& ray);

		void
		draw_pixel(RGBColor pixel_color, int c, int r) const;

		void
		display_image(void) const;

	private:

		void
		delete_objects(void);

		void
		delete_lights(void);
};


// ------------------------------------------------------------------ add_object

inline void
World::add_object(GeometricObject* object_ptr) {
	objects.push_back(object_ptr);
}

// ------------------------------------------------------------------ add_light
inline void
World::add_light(Light* light_ptr) {
	lights.push_back(light_ptr);
}

// ------------------------------------------------------------------ set_ambient_light

inline void
World::set_ambient_light(int light) {
	ambient = light;
}

#endif
