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

#include "Camera.h"

#include <utility>

Camera::~Camera() {}

Camera::Camera(const Camera& c) : eye(c.eye), lookat(c.lookat), ra(c.ra), up(c.up), u(c.u), v(c.v), w(c.w), exposure_time(c.exposure_time) {}

Camera::Camera(Camera&& c) noexcept
    : eye(std::move(c.eye)),
      lookat(std::move(c.lookat)),
      ra(std::exchange(c.ra, 0.0f)),
      up(std::move(c.up)),
      u(std::move(c.u)),
      v(std::move(c.v)),
      w(std::move(c.w)),
      exposure_time(std::exchange(c.exposure_time, 0.0f)) {}

Camera& Camera::operator=(const Camera& c) {
    eye = c.eye;
    lookat = c.lookat;
    ra = c.ra;
    up = c.up;
    u = c.u;
    v = c.v;
    w = c.w;
    exposure_time = c.exposure_time;

    return *this;
}

Camera& Camera::operator=(Camera&& c) noexcept {
    eye = std::move(c.eye);
    lookat = std::move(c.lookat);
    ra = std::exchange(c.ra, 0.0f);
    up = std::move(c.up);
    u = std::move(c.u);
    v = std::move(c.v);
    w = std::move(c.w);
    exposure_time = std::exchange(c.exposure_time, 0.0f);

    return *this;
}

// This computes an orthornormal basis given the view point, lookat point, and up vector
// TODO: call it everytime eye or lookat is updated
void Camera::compute_uvw() {
    w = eye - lookat;
    w.normalize();
    u = up ^ w;
    u.normalize();
    v = w ^ u;

    // take care of the singularity by hardwiring in specific camera orientations

    if (eye.x == lookat.x && eye.z == lookat.z && eye.y > lookat.y) {  // camera looking vertically down
        u = Vector3D(0.0f, 0.0f, 1.0f);
        v = Vector3D(1.0f, 0.0f, 0.0f);
        w = Vector3D(0.0f, 1.0f, 0.0f);
    }

    if (eye.x == lookat.x && eye.z == lookat.z && eye.y < lookat.y) {  // camera looking vertically up
        u = Vector3D(1.0f, 0.0f, 0.0f);
        v = Vector3D(0.0f, 0.0f, 1.0f);
        w = Vector3D(0.0f, -1.0f, 0.0f);
    }
}
