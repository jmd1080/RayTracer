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

		for (int r = 0; r < vp.vres; r++)
			for (int c = 0; c < vp.hres; c++) {
				//Create ray for pixel
				Vector3D rayDir = viewDir * d;

				//Get the intersection for the ray

			}
}
