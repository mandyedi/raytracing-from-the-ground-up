//  Copyright (C) Kevin Suffern 2000-2007.
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.
//  See the file COPYING.txt for the full license.

//  Copyright notice for changes since the originally published version:
//  Copyright (C) Eduárd Mándy 2019-2025
//  Though this C++ code was change in a large measure it still has the original copyright notice.
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.
//  See the file COPYING.txt for the full license.

#ifndef __PINHOLE__
#define __PINHOLE__

#include "../Utilities/Point2D.h"
#include "Camera.h"

class World;

class Pinhole : public Camera {
public:

    Pinhole() = default;

    ~Pinhole();

    Pinhole(const Pinhole& p);

    Pinhole(Pinhole&& p) noexcept;

    Pinhole& operator=(const Pinhole& p);

    Pinhole& operator=(Pinhole&& p) noexcept;

    Camera* clone() const override;

    void set_view_distance(const float vpd);

    void set_zoom(const float zoom_factor);

    Vector3D get_direction(const Point2D& p) const;

    void render_scene(const World& w, float x = 0.0f, int offset = 0) override;

private:

    float d = 500.0f;  // view plane distance
    float zoom = 1.0f;
};

inline void Pinhole::set_view_distance(float _d) { d = _d; }

inline void Pinhole::set_zoom(float zoom_factor) { zoom = zoom_factor; }

#endif
