//  Copyright (C) Kevin Suffern 2000-2007.
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.
//  See the file COPYING.txt for the full license.

//  Copyright notice for changes since the originally published version:
//  Copyright (C) Eduárd Mándy 2019-2021
//  Though this C++ code was change in a large measure it still has the original copyright notice.
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.
//  See the file COPYING.txt for the full license.

#ifndef __CAMERA__
#define __CAMERA__

// There is no view plane distance because the fisheye and panoramic cameras don't use it

#include "../Utilities/Point3D.h"
#include "../Utilities/Vector3D.h"

class World;  // can't #include "World" here because World contains a camera pointer


class Camera {
	public:
	
		Camera();   							// default constructor

		Camera(const Camera& camera);			// copy constructor
		
		virtual Camera*							// virtual copy constructor
		clone(void) const = 0;
		
		virtual
		~Camera();   							

		virtual void 																		
		render_scene(const World& w) = 0;
		
		void
		set_eye(const Point3D& p);

		void
		set_eye(const float x, const float y, const float z);
		
		void
		set_lookat(const Point3D& p);

		void
		set_lookat(const float x, const float y, const float z);

		void
		set_up_vector(const Vector3D& u);

		void
		set_up_vector(const float x, const float y, const float z);

		void
		set_roll(const float ra);
		
		void
		set_exposure_time(const float exposure);
		
		void									
		compute_uvw(void);
		
		
	protected:		
	
		Point3D			eye;				// eye point
		Point3D			lookat; 			// lookat point
		float			ra;					// roll angle
		Vector3D		up;					// up vector
		Vector3D		u, v, w;			// orthonormal basis vectors
		float			exposure_time;
		
		Camera& 							// assignment operator
		operator= (const Camera& camera);
};





inline void
Camera::set_eye(const Point3D& p) {
	eye = p;
}



inline void
Camera::set_eye(const float x, const float y, const float z) {
	eye.x = x; eye.y = y; eye.z = z;
}



inline void
Camera::set_lookat(const Point3D& p) {
	lookat = p;
}



inline void
Camera::set_lookat(const float x, const float y, const float z) {
	lookat.x = x; lookat.y = y; lookat.z = z;
}



inline void
Camera::set_up_vector(const Vector3D& u) {
	up = u;
}



inline void
Camera::set_up_vector(const float x, const float y, const float z) {
	up.x = x; up.y = y; up.z = z;
}



inline void
Camera::set_roll(const float r) { 
	ra = r;
}



inline void
Camera::set_exposure_time(const float exposure) {
	exposure_time = exposure;
}


#endif