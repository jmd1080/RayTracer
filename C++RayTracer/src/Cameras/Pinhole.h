/*
 * Pinhole.h
 *
 *  Created on: 3 Apr 2012
 *      Author: jamie
 */

#ifndef __PINHOLE__
#define __PINHOLE__

#include "Point2D.h"
#include "World.h"

class Pinhole {
	public:

		Pinhole();

		virtual
		~Pinhole();

		void
		set_view_distance(const float vpd);

		virtual void
		render_scene(const World& w);

	private:

		float	 d;         // view plane distance
		Point3D  camPos;    // the position of the pinhole camera
		Vector3D viewdir;   // the direction the camera is pointing
		float	 rollAngle; // the angle the camera is rotated at;

};




//-------------------------------------------------------------------------- set_vpd

inline void
Pinhole::set_view_distance(float _d) {
	d = _d;
}



//-------------------------------------------------------------------------- set_zoom

inline void
Pinhole::set_zoom(float zoom_factor) {
	zoom = zoom_factor;
}

#endif
