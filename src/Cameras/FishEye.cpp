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

#include "FishEye.h"

#include <utility>

#include "../Samplers/Sampler.h"
#include "../Tracers/Tracer.h"
#include "../Utilities/Point3D.h"
#include "../Utilities/RGBColor.h"
#include "../Utilities/Vector3D.h"
#include "../World/World.h"

FishEye::~FishEye() {}

FishEye::FishEye(const FishEye& fe) : Camera(fe), psi_max(fe.psi_max) {}

FishEye::FishEye(FishEye&& fe) noexcept : Camera(std::move(fe)), psi_max(std::exchange(fe.psi_max, 0.0f)) {}

FishEye& FishEye::operator=(const FishEye& fe) {
    Camera::operator=(fe);

    psi_max = fe.psi_max;

    return *this;
}

FishEye& FishEye::operator=(FishEye&& fe) noexcept {
    Camera::operator=(std::move(fe));

    psi_max = std::exchange(fe.psi_max, 0.0f);

    return *this;
}

Camera* FishEye::clone() const { return new FishEye(*this); }

Vector3D FishEye::ray_direction(const Point2D& pp, const int hres, const int vres, const float s, float& r_squared) const {
    // compute the normalized device coordinates

    Point2D pn(2.0f / (s * static_cast<float>(hres)) * pp.x, 2.0f / (s * static_cast<float>(vres)) * pp.y);
    r_squared = pn.x * pn.x + pn.y * pn.y;

    if (r_squared <= 1.0f) {
        float r = sqrtf(r_squared);
        float psi = r * psi_max * PI_ON_180;
        float sin_psi = sinf(psi);
        float cos_psi = cosf(psi);
        float sin_alpha = pn.y / r;
        float cos_alpha = pn.x / r;
        Vector3D dir = sin_psi * cos_alpha * u + sin_psi * sin_alpha * v - cos_psi * w;

        return dir;
    } else
        return Vector3D(0.0f);
}

void FishEye::render_scene(const World& wr, float x /*= 0*/, int offset /*= 0*/) {
    RGBColor L;
    int hres = wr.vp.hres;
    int vres = wr.vp.vres;
    float s = wr.vp.s;
    Ray ray;
    int depth = 0;
    Point2D sp;       // sample point in [0, 1] X [0, 1]
    Point2D pp;       // sample point on the pixel
    float r_squared;  // sum of squares of normalised device coordinates

    ray.o = eye;
    float inv_num_samples = 1.0f / static_cast<float>(wr.vp.num_samples);

    for (int r = 0; r < vres; r++)        // up
        for (int c = 0; c < hres; c++) {  // across
            L = RGBColor::black;

            for (int j = 0; j < wr.vp.num_samples; j++) {
                sp = wr.vp.sampler_ptr->sample_unit_square();
                pp.x = s * (c - 0.5f * hres + sp.x) + x;
                pp.y = s * (r - 0.5f * vres + sp.y);
                ray.d = ray_direction(pp, hres, vres, s, r_squared);

                if (r_squared <= 1.0f) {
                    L += wr.tracer_ptr->trace_ray(ray, depth);
                }
            }

            L *= inv_num_samples;
            L *= exposure_time;
            wr.display_pixel(r, c + offset, L);
        }

    wr.save_to_ppm();
}
