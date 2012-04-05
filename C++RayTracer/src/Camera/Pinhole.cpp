#include "../Utilities/Constants.h"
#include "../Utilities/Point3D.h"
#include "../Utilities/Vector3D.h"
#include "Pinhole.h"
#include <math.h>
#include "../Tracers/RayCast.h"



// ----------------------------------------------------------------------------- default constructor

Pinhole::Pinhole(void)
	:	d(500),
	 	camPos(Point3D(0)),
	 	viewDir(Vector3D(0,0,-1)),
		rollAngle(0)
{}


void
Pinhole::render_scene(const World& w)
{
		Ray	ray;
		ray.o = camPos;
		ViewPlane vp(w.vp);

		RGBColor pixel_color;

		Vector3D up1 = Vector3D(sin(rollAngle),cos(rollAngle),0);
		Vector3D right = -1 * (up1 ^ viewDir);
		right.normalize();
		Vector3D up = -1 * viewDir ^ right;
		up.normalize();


		//Vector3D up = Vector3D(0,1,0);
		//Vector3D right = Vector3D(1,0,0);

		for (int r = 0; r < vp.vres; r++) // row
			for (int c = 0; c < vp.hres; c++) { // column
				//Create ray for pixel
				Vector3D rayDir = viewDir * d;
				ray.o = camPos;

				//Get position on view plane
				rayDir+= (r - vp.vres/2)*up;

				rayDir+= (c - vp.hres/2)*right;

				rayDir.normalize();

				ray.d = rayDir;

				//Get the intersection for the ray
				pixel_color = w.tracer_ptr->trace_ray(ray);

				w.draw_pixel(pixel_color,c,r);
			}

		w.display_image();
}
