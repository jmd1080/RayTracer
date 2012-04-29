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


		// Constructor
		Pinhole();

		// Set the view distance to the plane
		void
		set_view_distance(const float dist);

		// Set the filename to output to
		void
		set_output(const string out);

		// Set the view
		void
		set_zoom(const float zoom);

		// Takes a 3D point and moves the camera there
		void
		set_camera_position(const Point3D pos);

		// Sets the rotation of the camera in radians
		void
		set_camera_roll(const float angle);

		// Sets the direction the camera is pointing in. Can take non-normalized vectors
		void
		set_camera_dir(const Vector3D dir);

		// Takes a world pointer and outputs the image according to the camera settings
		void
		render_scene(const World *w);

		// Sets the sample rate per pixel. Number of samples will be equal to s^2 to ensure it is always a square number
		void
		set_sample_rate(int s);

		// Sets the vertical resolution of the output image in pixels
		void
		set_vres(int v);

		// Sets the horizontal resolution of the output image in pixels
		void
		set_hres(int h);


	private:

		float		d;			// view plane distance
		Point3D		camPos;		// the position of the pin-hole camera
		Vector3D	viewDir;	// the direction the camera is pointing
		float		rollAngle;	// the angle the camera is rotated at;
		float		samples;	// square root of number of samples per pixel (ensuring samples is always a square number)
		int			vres;		// the vertical resolution of the output image
		int			hres;		// the horizontal resolution of the output image
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
