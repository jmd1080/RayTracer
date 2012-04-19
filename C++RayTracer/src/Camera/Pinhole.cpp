#include "../Utilities/Constants.h"
#include "../Utilities/Point3D.h"
#include "../Utilities/Vector3D.h"
#include "Pinhole.h"
#include <math.h>
#include <time.h>
#include "../Tracers/RayCast.h"

// ----------------------------------------------------------------------------- default constructor

Pinhole::Pinhole(void)
	:	d(500),
	 	camPos(Point3D(0)),
	 	viewDir(Vector3D(0,0,-1)),
		rollAngle(0),
		samples(1)
{}

void
Pinhole::render_scene(const World *w)
{
		Ray	ray;
		ray.o = camPos;
		ViewPlane vp(w->vp);
		RGBColor pixel_color;

		Vector3D up1 = Vector3D(sin(rollAngle),cos(rollAngle),0);
		Vector3D right = -1 * (up1 ^ viewDir);
		right.normalize();
		Vector3D up = -1 * viewDir ^ right;
		up.normalize();

		if (up.z > up.y && rollAngle < PI)
		{
			rollAngle += PI;
		}

		for (int r = 0; r < vp.vres; r++) // row
		{
			for (int c = 0; c < vp.hres; c++) { // column
				RGBColor pixel_col = RGBColor();
				// Anti-aliasing code
				for (int i = 0; i < samples; i++)
					for (int j = 0; j < samples; j++)
					{
						//Create ray for pixel
						Vector3D rayDir = viewDir * d;
						RGBColor sample_col = RGBColor();
						//Get position on view plane
						rayDir+= (r + (float)(i)/samples - 0.5 - vp.vres/2)*up;
						//printf("%f\n",(float)(j)/SAMPLES);

						rayDir+= (c + (float)(j)/samples - 0.5 - vp.hres/2)*right;

						rayDir.normalize();
						//printf("%f,%f,%f\n",rayDir.x,rayDir.y,rayDir.z);

						ray.d = rayDir;

						//Get the intersection for the ray
						sample_col = w->tracer_ptr->trace_ray(ray);

						pixel_col += sample_col;
					}

				pixel_col = pixel_col / (samples*samples);

				w->draw_pixel(pixel_col,c,r);


			}
		}

		w->display_image();
}
