#include "../Utilities/Constants.h"
#include "../Utilities/Point3D.h"
#include "../Utilities/Vector3D.h"
#include "Pinhole.h"
#include <math.h>


// ----------------------------------------------------------------------------- default constructor

Pinhole::Pinhole(void)
	:	d(500)
	 	//camPos(Point3D(0))
	 	//viewdir(Vector3D(0,0,1))
{}


void
Pinhole::render_scene(const World& w)
{
		Ray	ray;
		ray.o = camPos;
		ViewPlane vp(w.vp);

		RGBColor pixel_color;

		// GET BY ROTATION TRANSFORM!
		Vector3D up = Vector3D(0,1,0);
		Vector3D right = Vector3D(1,0,0);

		for (int r = 0; r < vp.vres; r++) // row
			for (int c = 0; c < vp.hres; c++) { // column
				//Create ray for pixel
				Vector3D rayDir = viewDir * d;

				//Get position on view plane
				rayDir+= (r - vp.vres/2)*up;
				rayDir+= (c - vp.hres/2)*right;

				rayDir.normalize();

				//Get the intersection for the ray
				//pixel_color = tracer_ptr->trace_ray(ray);

			}
}
