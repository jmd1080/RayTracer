/*
 * Pinhole.h
 *
 *  Created on: 3 Apr 2012
 *      Author: jamie
 */

#ifndef __PINHOLE__
#define __PINHOLE__

#include "../Utilities/Vector3D.h"
#include "../Utilities/Point3D.h"
#include "../Utilities/Point3D.h"
#include "../World/World.h"

class Pinhole {
	public:

		Pinhole();

		void
		set_view_distance(const float dist);

		void
		set_output(const string out);

		void
		set_zoom(const float zoom);

		void
		set_camera_position(const Point3D pos);

		void
		set_camera_roll(const float angle);

		void
		set_camera_dir(const Vector3D dir);

		void
		render_scene(const World *w);

		void
		set_sample_rate(int s);

		void
		set_vres(int v);

		void
		set_hres(int h);

		float
		poisson();

	private:

		float		d;			// view plane distance
		Point3D		camPos;		// the position of the pin-hole camera
		Vector3D	viewDir;	// the direction the camera is pointing
		float		rollAngle;	// the angle the camera is rotated at;
		float		samples;	// square root of number of samples per pixel (ensuring samples is always a whole number)
		int			vres;
		int			hres;
		IplImage*	img;		//The output image of the camera
		float		zoom;		//How zoomed in the camera is

		string 		output;     //The file to be output

		void
		draw_pixel(RGBColor pixel_color, int c, int r) const;
};

inline void
Pinhole::set_view_distance(float dist) {
	d = dist;
}

inline void
Pinhole::set_output(string out) {
	output = out;
}

inline void
Pinhole::set_zoom(float z) {
	zoom = 1/z;
}

inline void
Pinhole::set_camera_position(Point3D pos) {
	camPos = pos;
}

inline void
Pinhole::set_sample_rate(int s) {
	samples = (float)s;
}

inline void
Pinhole::set_camera_roll(float angle) {
	rollAngle = angle;
}

inline void
Pinhole::set_camera_dir(Vector3D dir) {
	viewDir = dir;
	viewDir.normalize();
}

inline void
Pinhole::set_vres(int v) {
	vres = v;
}

inline void
Pinhole::set_hres(int h) {
	hres = h;
}

#endif
