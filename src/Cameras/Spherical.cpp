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

#include "Spherical.h"

#include <utility>

#include "../Samplers/Sampler.h"
#include "../Tracers/Tracer.h"
#include "../Utilities/Maths.h"
#include "../Utilities/Point3D.h"
#include "../Utilities/RGBColor.h"
#include "../Utilities/Vector3D.h"
#include "../World/World.h"

Spherical::~Spherical() {}

Spherical::Spherical(const Spherical& s) : Camera(s), lambda_max(s.lambda_max), psi_max(s.psi_max) {}

Spherical::Spherical(Spherical&& s) noexcept : Camera(std::move(s)), lambda_max(std::exchange(s.lambda_max, 0.0f)), psi_max(std::exchange(s.psi_max, 0.0f)) {}

Spherical& Spherical::operator=(const Spherical& s) {
    Camera::operator=(s);

    lambda_max = s.lambda_max;
    psi_max = s.psi_max;

    return *this;
}

Spherical& Spherical::operator=(Spherical&& s) noexcept {
    Camera::operator=(std::move(s));

    lambda_max = std::exchange(s.lambda_max, 0.0f);
    psi_max = std::exchange(s.psi_max, 0.0f);

    return *this;
}

Camera* Spherical::clone() const { return new Spherical(*this); }

Vector3D Spherical::ray_direction(const Point2D& pp, const int hres, const int vres, const float s) const {
    // compute the normalized device coordinates

    Point2D pn(2.0f / (s * static_cast<float>(hres)) * pp.x, 2.0f / (s * static_cast<float>(vres)) * pp.y);

    // compute the angles lambda and psi in radians

    float lambda = pn.x * degreeToRadian(lambda_max);
    float psi = pn.y * degreeToRadian(psi_max);

    // compute the sherical azimuth and polar angles

    float phi = PI - lambda;
    float theta = 0.5f * PI - psi;

    float sin_phi = sinf(phi);
    float cos_phi = cosf(phi);
    float sin_theta = sinf(theta);
    float cos_theta = cosf(theta);

    Vector3D dir = sin_theta * sin_phi * u + cos_theta * v + sin_theta * cos_phi * w;

    return dir;
}

void Spherical::render_scene(const World& wr, float x /*= 0*/, int offset /*= 0*/) {
    RGBColor L;
    int hres = wr.vp.hres;
    int vres = wr.vp.vres;
    float s = wr.vp.s;
    Ray ray;
    int depth = 0;
    Point2D sp;  // sample point in [0, 1] X [0, 1]
    Point2D pp;  // sample point on the pixel

    ray.o = eye;
    float inv_num_samples = 1.0f / static_cast<float>(wr.vp.num_samples);

    for (int r = 0; r < vres; r++)        // up
        for (int c = 0; c < hres; c++) {  // across
            L = RGBColor::black;

            for (int j = 0; j < wr.vp.num_samples; j++) {
                sp = wr.vp.sampler_ptr->sample_unit_square();
                pp.x = s * (static_cast<float>(c) - 0.5f * static_cast<float>(hres) + sp.x) + x;
                pp.y = s * (static_cast<float>(r) - 0.5f * static_cast<float>(vres) + sp.y);
                ray.d = ray_direction(pp, hres, vres, s);

                L += wr.tracer_ptr->trace_ray(ray, depth);
            }

            L *= inv_num_samples;
            L *= exposure_time;
            wr.display_pixel(r, c + offset, L);
        }

    wr.save_to_ppm();
}
