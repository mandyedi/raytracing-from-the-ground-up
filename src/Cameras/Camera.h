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

    Camera() = default;

    virtual ~Camera();

    Camera(const Camera& c);

    Camera(Camera&& c) noexcept;

    Camera& operator=(const Camera& c);

    Camera& operator=(Camera&& c) noexcept;

    virtual Camera* clone(void) const = 0;

    // In chapter 12.5 Implementation (Stereoscopy) there is a separate function called
    // Pinhole::render_stereo(World& w, float, int offset)
    // I found it simpler to just extend the original Camera::render_scene method with the x and offset arguments.
    virtual void render_scene(const World& w, float x = 0.0f, int offset = 0) = 0;

    void set_eye(const Point3D& p);

    void set_eye(const float x, const float y, const float z);

    void set_lookat(const Point3D& p);

    void set_lookat(const float x, const float y, const float z);

    void set_up_vector(const Vector3D& u);

    void set_up_vector(const float x, const float y, const float z);

    void set_roll(const float ra);

    void set_exposure_time(const float exposure);

    void compute_uvw(void);

protected:

    Point3D eye = Point3D(0.0f, 0.0f, 500.0f);  // eye point
    Point3D lookat = Point3D(0.0f);             // lookat point
    float ra = 0.0f;                            // roll angle
    Vector3D up = Vector3D(0.0f, 0.1f, 0.0f);   // up vector
    Vector3D u = Vector3D(1.0f, 0.0f, 0.0f);    // orthonormal basis vectors
    Vector3D v = Vector3D(0.0f, 0.1f, 0.0f);
    Vector3D w = Vector3D(0.0f, 0.0f, 1.0f);
    float exposure_time = 1.0f;
};

inline void Camera::set_eye(const Point3D& p) { eye = p; }

inline void Camera::set_eye(const float x, const float y, const float z) {
    eye.x = x;
    eye.y = y;
    eye.z = z;
}

inline void Camera::set_lookat(const Point3D& p) { lookat = p; }

inline void Camera::set_lookat(const float x, const float y, const float z) {
    lookat.x = x;
    lookat.y = y;
    lookat.z = z;
}

inline void Camera::set_up_vector(const Vector3D& u) { up = u; }

inline void Camera::set_up_vector(const float x, const float y, const float z) {
    up.x = x;
    up.y = y;
    up.z = z;
}

inline void Camera::set_roll(const float r) { ra = r; }

inline void Camera::set_exposure_time(const float exposure) { exposure_time = exposure; }

#endif
