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

#include "FresnelReflector.h"

#include <cmath>
#include <utility>

#include "../Utilities/ShadeRec.h"
#include "../Utilities/Vector3D.h"

FresnelReflector::FresnelReflector(const FresnelReflector& fr) : BRDF(fr), eta_in(fr.eta_in), eta_out(fr.eta_out) {}

FresnelReflector::FresnelReflector(FresnelReflector&& fr) noexcept : BRDF(std::move(fr)), eta_in(std::exchange(fr.eta_in, 1.0f)), eta_out(std::exchange(fr.eta_out, 1.0f)) {}

FresnelReflector& FresnelReflector::operator=(const FresnelReflector& fr) {
    FresnelReflector::operator=(fr);
    eta_in = fr.eta_in;
    eta_out = fr.eta_out;

    return *this;
}

FresnelReflector& FresnelReflector::operator=(FresnelReflector&& fr) noexcept {
    FresnelReflector::operator=(fr);
    eta_in = std::exchange(fr.eta_in, 1.0f);
    eta_out = std::exchange(fr.eta_out, 1.0f);

    return *this;
}

FresnelReflector* FresnelReflector::clone() const { return new FresnelReflector(*this); }

RGBColor FresnelReflector::sample_f(const ShadeRec& sr, const Vector3D& wo, Vector3D& wr) const {
    float ndotwo = sr.normal * wo;
    wr = -wo + 2.0f * sr.normal * ndotwo;
    return fresnel(sr) * RGBColor::white / fabs(sr.normal * wr);
}

float FresnelReflector::fresnel(const ShadeRec& sr) const {
    Normal normal(sr.normal);
    float ndotd = -normal * sr.ray.d;
    float eta;

    if (ndotd < 0.0f) {
        normal = -normal;
        eta = eta_out / eta_in;
    } else {
        eta = eta_in / eta_out;
    }

    float cos_theta_i = -normal * sr.ray.d;
    float temp = 1.0f - (1.0f - cos_theta_i * cos_theta_i) / (eta * eta);
    float cos_theta_t = sqrt(1.0f - (1.0f - cos_theta_i * cos_theta_i) / (eta * eta));
    float r_parallel = (eta * cos_theta_i - cos_theta_t) / (eta * cos_theta_i + cos_theta_t);
    float r_perpendicular = (cos_theta_i - eta * cos_theta_t) / (cos_theta_i + eta * cos_theta_t);
    float kr = 0.5f * (r_parallel * r_parallel + r_perpendicular * r_perpendicular);

    return kr;
}
