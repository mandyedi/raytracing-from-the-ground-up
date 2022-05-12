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

#ifndef __THINLENS__
#define __THINLENS__

#include "Camera.h"

class Point2D;
class World;
class Sampler;

class ThinLens : public Camera {
public:

    ThinLens() = default;

    ~ThinLens();

    ThinLens(const ThinLens& tl);

    ThinLens(ThinLens&& tl) noexcept;

    ThinLens& operator=(const ThinLens& tl);

    ThinLens& operator=(ThinLens&& tl) noexcept;

    Camera* clone(void) const override;

    void set_sampler(Sampler* sp);

    Vector3D ray_direction(const Point2D& pixel_point, const Point2D& lens_point) const;

    void render_scene(const World& w, float x = 0.0f, int offset = 0) override;

    void set_view_distance(float distance);

    void set_focal_distance(float distance);

    void set_lens_radius(float radius);

private:

    float lens_radius = 1.0f;        // lens radius
    float d = 500.0f;                // view plane distance
    float f = 100.0f;                // focal distance
    float zoom = 1.0f;               // zoom factor
    Sampler* sampler_ptr = nullptr;  // sampler object
};

inline void ThinLens::set_view_distance(float distance) { d = distance; }

inline void ThinLens::set_focal_distance(float distance) { f = distance; }

inline void ThinLens::set_lens_radius(float radius) { lens_radius = radius; }

#endif
