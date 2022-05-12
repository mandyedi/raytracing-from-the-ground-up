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

#include "BRDF.h"

#include "../Utilities/RGBColor.h"

BRDF::~BRDF(void) {
    if (sampler_ptr != nullptr) {
        delete sampler_ptr;
        sampler_ptr = nullptr;
    }
}

BRDF::BRDF(const BRDF& b) { sampler_ptr = b.sampler_ptr->clone(); }

BRDF::BRDF(BRDF&& b) noexcept : sampler_ptr(std::exchange(b.sampler_ptr, nullptr)) {}

BRDF& BRDF::operator=(const BRDF& b) {
    if (sampler_ptr) {
        delete sampler_ptr;
    }
    sampler_ptr = b.sampler_ptr->clone();

    return (*this);
}

BRDF& BRDF::operator=(BRDF&& b) noexcept {
    if (sampler_ptr) {
        delete sampler_ptr;
    }
    sampler_ptr = b.sampler_ptr;
    b.sampler_ptr = nullptr;

    return (*this);
}

void BRDF::set_sampler(Sampler* sPtr) {
    sampler_ptr = sPtr;
    sampler_ptr->map_samples_to_hemisphere(1);  // for perfect diffuse
}

RGBColor BRDF::f([[maybe_unused]] const ShadeRec& sr, [[maybe_unused]] const Vector3D& wo, [[maybe_unused]] const Vector3D& wi) const { return (RGBColor::black); }

RGBColor BRDF::sample_f([[maybe_unused]] const ShadeRec& sr, [[maybe_unused]] const Vector3D& wo, [[maybe_unused]] Vector3D& wi) const { return (RGBColor::black); }

RGBColor BRDF::sample_f([[maybe_unused]] const ShadeRec& sr, [[maybe_unused]] const Vector3D& wo, [[maybe_unused]] Vector3D& wi, [[maybe_unused]] float& pdf) const { return (RGBColor::black); }

RGBColor BRDF::rho([[maybe_unused]] const ShadeRec& sr, [[maybe_unused]] const Vector3D& wo) const { return (RGBColor::black); }
