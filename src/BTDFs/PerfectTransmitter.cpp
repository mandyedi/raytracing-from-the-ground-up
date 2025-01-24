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

#include "PerfectTransmitter.h"

#include <utility>
#include <cmath>

#include "../Utilities/Vector3D.h"
#include "../Utilities/ShadeRec.h"

PerfectTransmitter::PerfectTransmitter(const PerfectTransmitter& pt) : BTDF(pt), kt(pt.kt), ior(pt.ior) {}

PerfectTransmitter::PerfectTransmitter(PerfectTransmitter&& pt) noexcept : BTDF(std::move(pt)), kt(std::exchange(pt.kt, 0.0f)), ior(std::exchange(pt.ior, 1.0f)) {}

PerfectTransmitter& PerfectTransmitter::operator=(const PerfectTransmitter& pt) {
    PerfectTransmitter::operator=(pt);
    kt = pt.kt;
    ior = pt.ior;

    return *this;
}

PerfectTransmitter& PerfectTransmitter::operator=(PerfectTransmitter&& pt) noexcept {
    PerfectTransmitter::operator=(pt);
    kt = std::exchange(pt.kt, 0.0f);
    ior = std::exchange(pt.ior, 1.0f);

    return *this;
}

PerfectTransmitter* PerfectTransmitter::clone() const { return new PerfectTransmitter(*this); }

// tests for total internal reflection

bool PerfectTransmitter::tir(const ShadeRec& sr) const {
    Vector3D wo(-sr.ray.d);
    float cos_thetai = sr.normal * wo;
    float eta = ior;

    if (cos_thetai < 0.0f) {
        eta = 1.0f / eta;
    }

    return 1.0f - (1.0f - cos_thetai * cos_thetai) / (eta * eta) < 0.0f;
}

RGBColor PerfectTransmitter::f(const ShadeRec& sr, const Vector3D& wo, const Vector3D& wi) const { return RGBColor::black; }

// this computes the direction wt for perfect transmission
// and returns the transmission coefficient
// this is only called when there is no total internal reflection

RGBColor PerfectTransmitter::sample_f(const ShadeRec& sr, const Vector3D& wo, Vector3D& wt) const {
    Normal n(sr.normal);
    float cos_thetai = n * wo;
    float eta = ior;

    if (cos_thetai < 0.0f) {  // transmitted ray is outside
        cos_thetai = -cos_thetai;
        n = -n;            // reverse direction of normal
        eta = 1.0f / eta;  // invert ior
    }

    float temp = 1.0f - (1.0f - cos_thetai * cos_thetai) / (eta * eta);
    float cos_theta2 = sqrt(temp);
    wt = -wo / eta - (cos_theta2 - cos_thetai / eta) * n;

    return kt / (eta * eta) * RGBColor::white / fabs(sr.normal * wt);
}

RGBColor PerfectTransmitter::rho(const ShadeRec& sr, const Vector3D& wo) const { return RGBColor::black; }
