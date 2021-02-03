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

typedef enum {
	parallel,
	transverse
} ViewingType;

#include "../Utilities/Point2D.h"
#include "../World/World.h"

class StereoCamera: public Camera {
	public:

		StereoCamera();

		StereoCamera(Camera* left_camera, Camera* right_camera);

		StereoCamera(const StereoCamera& ph);

		virtual Camera*
		clone(void) const override;

		StereoCamera&
		operator= (const StereoCamera& rhs);

		virtual
		~StereoCamera();

		void
		setup_cameras(void);

		virtual void
		render_scene(const World& w, float x = 0, int offset = 0) override;

		void
		use_parallel_viewing();

		void
		use_transverse_viewing();

		void
		set_pixel_gap(int gap);

		void
		set_stereo_angle(float angle);

	private:

		ViewingType	viewing_type;		// parallel or transverse viewing
		int			pixel_gap;			// gap in pixels between the left and right images
		float		beta;				// stereo separation angle
		Camera*		left_camera_ptr;	// left eye camera
		Camera*		right_camera_ptr;	// right eye camera
};

inline void
StereoCamera::use_parallel_viewing() {
	viewing_type = ViewingType::parallel;
}

inline void
StereoCamera::use_transverse_viewing() {
	viewing_type = ViewingType::transverse;
}

inline void
StereoCamera::set_pixel_gap(int gap) {
	pixel_gap = gap;
}

inline void
StereoCamera::set_stereo_angle(float angle) {
	beta = angle;
}
