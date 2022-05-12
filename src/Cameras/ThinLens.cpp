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

#include "ThinLens.h"

#include "../Samplers/Sampler.h"
#include "../Tracers/Tracer.h"
#include "../World/World.h"

ThinLens::~ThinLens(void) {
    if (sampler_ptr != nullptr) {
        delete sampler_ptr;
        sampler_ptr = nullptr;
    }
}

ThinLens::ThinLens(const ThinLens& tl) : Camera(tl), lens_radius(tl.lens_radius), d(tl.d), f(tl.f), zoom(tl.zoom) { sampler_ptr = tl.sampler_ptr->clone(); }

ThinLens::ThinLens(ThinLens&& tl) noexcept
    : Camera(std::move(tl)),
      lens_radius(std::exchange(tl.lens_radius, 0.0f)),
      d(std::exchange(tl.d, 0.0f)),
      f(std::exchange(tl.f, 0.0f)),
      zoom(std::exchange(tl.zoom, 0.0f)),
      sampler_ptr(std::exchange(tl.sampler_ptr, nullptr)) {}

ThinLens& ThinLens::operator=(const ThinLens& tl) {
    Camera::operator=(tl);

    lens_radius = tl.lens_radius;
    d = tl.d;
    f = tl.f;
    zoom = tl.zoom;

    if (sampler_ptr != nullptr) {
        delete sampler_ptr;
    }
    sampler_ptr = tl.sampler_ptr->clone();

    return (*this);
}

ThinLens& ThinLens::operator=(ThinLens&& tl) noexcept {
    Camera::operator=(std::move(tl));

    lens_radius = std::exchange(tl.lens_radius, 0.0f);
    d = std::exchange(tl.d, 0.0f);
    f = std::exchange(tl.f, 0.0f);
    zoom = std::exchange(tl.zoom, 0.0f);

    if (sampler_ptr != nullptr) {
        delete sampler_ptr;
    }
    sampler_ptr = tl.sampler_ptr;
    tl.sampler_ptr = nullptr;

    return (*this);
}

Camera* ThinLens::clone(void) const { return (new ThinLens(*this)); }

void ThinLens::set_sampler(Sampler* sp) {
    if (sampler_ptr) {
        delete sampler_ptr;
        sampler_ptr = NULL;
    }

    sampler_ptr = sp;
    sampler_ptr->map_samples_to_unit_disk();
}

Vector3D ThinLens::ray_direction(const Point2D& pixel_point, const Point2D& lens_point) const {
    Point2D p(pixel_point.x * f / d, pixel_point.y * f / d);  // hit point on focal plane
    Vector3D dir = (p.x - lens_point.x) * u + (p.y - lens_point.y) * v - f * w;
    dir.normalize();

    return (dir);
}

void ThinLens::render_scene(const World& w, float x /*= 0*/, int offset /*= 0*/) {
    RGBColor L;
    Ray ray;
    int depth = 0;

    Point2D sp;  // sample point in [0, 1] X [0, 1]
    Point2D pp;  // sample point on a pixel
    Point2D dp;  // sample point on unit disk
    Point2D lp;  // sample point on lens

    float s = w.vp.s / zoom;

    float inv_num_samples = 1.0f / static_cast<float>(w.vp.num_samples);

    for (int r = 0; r < w.vp.vres; r++)        // up
        for (int c = 0; c < w.vp.hres; c++) {  // across
            L = RGBColor::black;

            for (int n = 0; n < w.vp.num_samples; n++) {
                sp = w.vp.sampler_ptr->sample_unit_square();
                pp.x = s * (static_cast<float>(c) - static_cast<float>(w.vp.hres) / 2.0f + sp.x) + x;
                pp.y = s * (static_cast<float>(r) - static_cast<float>(w.vp.vres) / 2.0f + sp.y);

                dp = sampler_ptr->sample_unit_disk();
                lp = dp * lens_radius;

                ray.o = eye + lp.x * u + lp.y * v;
                ray.d = ray_direction(pp, lp);
                L += w.tracer_ptr->trace_ray(ray, depth);
            }

            L *= inv_num_samples;
            L *= exposure_time;
            w.display_pixel(r, c + offset, L);
        }
}
