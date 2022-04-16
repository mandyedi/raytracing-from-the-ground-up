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

#include "StereoCamera.h"
#include "Pinhole.h"
#include "../Utilities/RGBColor.h"
#include "../Utilities/Point3D.h"
#include "../Utilities/Vector3D.h"
#include "../Utilities/Maths.h"
#include "../Samplers/Sampler.h"
#include "../World/ViewPlane.h"

StereoCamera::StereoCamera(void)
    :   Camera(),
        left_camera_ptr(new Pinhole),
        right_camera_ptr(new Pinhole)
{}

StereoCamera::StereoCamera(Camera *left_camera, Camera *right_camera)
    :   Camera(),
        left_camera_ptr(left_camera),
        right_camera_ptr(right_camera)
{}

StereoCamera::~StereoCamera(void) {
    if (left_camera_ptr != nullptr) {
        delete left_camera_ptr;
        left_camera_ptr = nullptr;
    }

    if (right_camera_ptr != nullptr) {
        delete right_camera_ptr;
        right_camera_ptr = nullptr;
    }
}

StereoCamera::StereoCamera(const StereoCamera& c)
    :   Camera(c),
        viewing_type(c.viewing_type),
        pixel_gap(c.pixel_gap),
        beta(c.beta)
{
    left_camera_ptr = c.left_camera_ptr->clone();
    right_camera_ptr = c.right_camera_ptr->clone();
}

StereoCamera::StereoCamera(StereoCamera&& sc) noexcept
    :   Camera(std::move(sc)),
        viewing_type(std::exchange(sc.viewing_type, ViewingType::Parallel)),
        pixel_gap(std::exchange(sc.pixel_gap, 0)),
        beta(std::exchange(sc.beta, 0.0f)),
        left_camera_ptr(std::exchange(sc.left_camera_ptr, nullptr)),
        right_camera_ptr(std::exchange(sc.right_camera_ptr, nullptr))
{}

StereoCamera&
StereoCamera::operator= (const StereoCamera& sc) {
    Camera::operator= (sc);

    viewing_type = sc.viewing_type;
    pixel_gap = sc.pixel_gap;
    beta = sc.beta;

    if (left_camera_ptr != nullptr) {
        delete left_camera_ptr;
    }
    left_camera_ptr = sc.left_camera_ptr->clone();

    if (right_camera_ptr != nullptr) {
        delete right_camera_ptr;
    }
    right_camera_ptr = sc.right_camera_ptr->clone();

    return (*this);
}

StereoCamera&
StereoCamera::operator= (StereoCamera&& sc) noexcept {
    Camera::operator= (std::move(sc));

    viewing_type = std::exchange(sc.viewing_type, ViewingType::Parallel);
    pixel_gap = std::exchange(sc.pixel_gap, 0);
    beta = std::exchange(sc.beta, 0.0f);

    if (left_camera_ptr != nullptr) {
        delete left_camera_ptr;
    }
    left_camera_ptr = sc.left_camera_ptr;
    sc.left_camera_ptr = nullptr;


    if (right_camera_ptr != nullptr) {
        delete right_camera_ptr;
    }
    right_camera_ptr = sc.right_camera_ptr;
    sc.right_camera_ptr = nullptr;

    return *this;
}

Camera*
StereoCamera::clone(void) const {
    return (new StereoCamera(*this));
}

void
StereoCamera::setup_cameras(void) {
    float r = eye.distance(lookat);
    float x = r * tan(0.5 * degreeToRadian(beta));  //  half the camera separation distance

    left_camera_ptr->set_eye(eye - x * u);
    left_camera_ptr->set_lookat(lookat - x * u);
    left_camera_ptr->compute_uvw();

    right_camera_ptr->set_eye(eye + x * u);
    right_camera_ptr->set_lookat(lookat + x * u);
    right_camera_ptr->compute_uvw();
}

void
StereoCamera::render_scene(const World& w, float x /*= 0*/, int offset /*= 0*/) {
    int         hres    = w.vp.hres;
    int         vres    = w.vp.vres;

    float r = eye.distance(lookat);
    float x2 = r * tanf(0.5f * degreeToRadian(beta));

    if (viewing_type == ViewingType::Parallel) {
        left_camera_ptr->render_scene(w, x2, 0);                        // left view on left
        right_camera_ptr->render_scene(w, -x2, hres + pixel_gap);       // right view on right
    }

    if (viewing_type == ViewingType::Transverse) {
        right_camera_ptr->render_scene(w, -x2, 0);                      // right view on left
        left_camera_ptr->render_scene(w, x2, hres + pixel_gap);         // left view on right
    }
}
