#include "../Utilities/Constants.h"
#include "../Utilities/Point3D.h"
#include "../Utilities/Vector3D.h"
#include "Pinhole.h"
#include <math.h>
#include <time.h>
#include "../Tracers/RayCast.h"
#include <opencv/cv.h>
#include <opencv/highgui.h>

// ----------------------------------------------------------------------------- default constructor

Pinhole::Pinhole(void)
	:	d(500),
	 	camPos(Point3D(0)),
	 	viewDir(Vector3D(0,0,-1)),
		rollAngle(0),
		samples(1),
		hres(0),
		vres(0)
{}

void
Pinhole::draw_pixel(RGBColor pixel_color, int c, int r) const
{
	if (img == NULL)
		return;
	if (c >= img->height || r >= img->width)
		return;
	CvScalar s = cvGet2D(img,c,r);
	s.val[0] = pixel_color.b*255;
	s.val[1] = pixel_color.g*255;
	s.val[2] = pixel_color.r*255;

	cvSet2D(img,c,r,s);

}

void
Pinhole::render_scene(const World *w)
{
		img = cvCreateImage(cvSize(hres,vres), 8, 3);
		Ray	ray;
		ray.o = camPos;
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

		for (int r = 0; r < hres; r++) // row
		{
			for (int c = 0; c < vres; c++) { // column
				RGBColor pixel_col = RGBColor();
				// Anti-aliasing code
				for (int i = 0; i < samples; i++)
					for (int j = 0; j < samples; j++)
					{
						//Create ray for pixel
						Vector3D rayDir = viewDir * d;
						RGBColor sample_col = RGBColor();
						//Get position on view plane
						rayDir+= (r + (float)(i)/samples - 0.5 - hres/2)*up;
						//printf("%f\n",(float)(j)/SAMPLES);

						rayDir+= (c + (float)(j)/samples - 0.5 - vres/2)*right;

						rayDir.normalize();
						//printf("%f,%f,%f\n",rayDir.x,rayDir.y,rayDir.z);

						ray.d = rayDir;

						//Get the intersection for the ray
						sample_col = w->tracer_ptr->trace_ray(ray);

						pixel_col += sample_col;
					}

				pixel_col = pixel_col / (samples*samples);

				draw_pixel(pixel_col,c,r);
			}
		}

		cvShowImage("Image",img);
		cvSaveImage("out.jpg",img,0);
		cvWaitKey(0);
}
