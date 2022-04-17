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

#include <math.h>
#include "Orthographic.h"
#include "../World/World.h"
#include "../Utilities/RGBColor.h"
#include "../Utilities/Point3D.h"
#include "../Utilities/Vector3D.h"
#include "../Samplers/Sampler.h"
#include "../Tracers/Tracer.h"

Orthographic::~Orthographic(void) {}



Orthographic::Orthographic(const Orthographic& p)
    :   Camera(p)
{}



Orthographic::Orthographic(Orthographic&& p) noexcept
    :   Camera(std::move(p))
{}



Orthographic&
Orthographic::operator= (const Orthographic& p) {
    Camera::operator= (p);

    return (*this);
}



Orthographic&
Orthographic::operator= (Orthographic&& p) noexcept {
    Camera::operator= (std::move(p));

    return (*this);
}



Camera*
Orthographic::clone(void) const {
    return (new Orthographic(*this));
}



void
Orthographic::render_scene(const World& w, float x /*= 0*/, int offset /*= 0*/) {
    RGBColor    L;
    Ray         ray;
    int         depth = 0;
    Point2D     sp;     // sample point in [0, 1] x [0, 1]
    Point2D     pp;     // sample point on a pixel
    float       zw = 100.0f;
    float       s = w.vp.s;

    ray.d = -(this->w);

    float inv_num_samples = 1.0f / static_cast<float>(w.vp.num_samples);

    for (int row = 0; row < w.vp.vres; row++) {                     // up
        for (int column = 0; column < w.vp.hres; column++) {        // across
            L = RGBColor::black;

            for (int j = 0; j < w.vp.num_samples; j++) {
                sp = w.vp.sampler_ptr->sample_unit_square();
                pp.x = s * (static_cast<float>(column) - 0.5f * static_cast<float>(w.vp.hres) + sp.x) + x;
                pp.y = s * (row - 0.5f * static_cast<float>(w.vp.vres) + sp.y);
                ray.o = eye + pp.x * u + pp.y * v;
                L += w.tracer_ptr->trace_ray(ray, depth);
            }

            L *= inv_num_samples;
            L *= exposure_time;
            w.display_pixel(row, column + offset, L);
        }
    }

    w.save_to_ppm();
}
