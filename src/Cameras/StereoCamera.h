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

#include "../Utilities/Point2D.h"
#include "Camera.h"

class World;

class StereoCamera : public Camera {
public:

    StereoCamera();

    StereoCamera(Camera* left_camera, Camera* right_camera);

    ~StereoCamera();

    StereoCamera(const StereoCamera& sc);

    StereoCamera(StereoCamera&& sc) noexcept;

    StereoCamera& operator=(const StereoCamera& sc);

    StereoCamera& operator=(StereoCamera&& sc) noexcept;

    Camera* clone() const override;

    void setup_cameras();

    void render_scene(const World& w, float x = 0.0f, int offset = 0) override;

    void use_parallel_viewing();

    void use_transverse_viewing();

    void set_pixel_gap(int gap);

    void set_stereo_angle(float angle);

private:

    enum class ViewingType { Parallel, Transverse };

    ViewingType viewing_type = ViewingType::Parallel;  // parallel or transverse viewing
    int pixel_gap = 5;                                 // gap in pixels between the left and right images
    float beta = 5.0f;                                 // stereo separation angle
    Camera* left_camera_ptr = nullptr;                 // left eye camera
    Camera* right_camera_ptr = nullptr;                // right eye camera
};

inline void StereoCamera::use_parallel_viewing() { viewing_type = ViewingType::Parallel; }

inline void StereoCamera::use_transverse_viewing() { viewing_type = ViewingType::Transverse; }

inline void StereoCamera::set_pixel_gap(int gap) { pixel_gap = gap; }

inline void StereoCamera::set_stereo_angle(float angle) { beta = angle; }
