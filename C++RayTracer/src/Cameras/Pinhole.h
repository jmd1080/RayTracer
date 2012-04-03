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
		set_view_distance(const float vpd);

		void
		set_camera_position(const Point3D pos);

		void
		set_camera_roll(const float angle);

		void
		set_camera_dir(const Vector3D dir);

		void
		render_scene(const World& w);

	private:

		float	 d;         // view plane distance
		Point3D  camPos;    // the position of the pin-hole camera
		Vector3D viewDir;   // the direction the camera is pointing
		float	 rollAngle; // the angle the camera is rotated at;
};

inline void
Pinhole::set_view_distance(float _d) {
	d = _d;
}

inline void
Pinhole::set_camera_position(Point3D pos) {
	camPos = pos;
}

inline void
Pinhole::set_camera_roll(float angle) {
	rollAngle = angle;
}

inline void
Pinhole::set_camera_dir(Vector3D dir) {
	viewDir = dir;
}

#endif
