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

#ifndef __PERFECT_TRANSMITTER__
#define __PERFECT_TRANSMITTER__

#include "BTDF.h"

class PerfectTransmitter : public BTDF {
public:

    PerfectTransmitter() = default;

    ~PerfectTransmitter() = default;

    PerfectTransmitter(const PerfectTransmitter& pt);

    PerfectTransmitter(PerfectTransmitter&& pt) noexcept;

    PerfectTransmitter& operator=(const PerfectTransmitter& rhs);

    PerfectTransmitter& operator=(PerfectTransmitter&& rhs) noexcept;

    PerfectTransmitter* clone() const override;

    void set_kt(const float k);

    void set_ior(const float eta);

    bool tir(const ShadeRec& sr) const;

    RGBColor f(const ShadeRec& sr, const Vector3D& wo, const Vector3D& wi) const override;

    RGBColor sample_f(const ShadeRec& sr, const Vector3D& wo, Vector3D& wt) const override;

    RGBColor rho(const ShadeRec& sr, const Vector3D& wo) const override;

private:

    float kt = 0.0f;   // transmission coefficient
    float ior = 1.0f;  // index of refraction
};

inline void PerfectTransmitter::set_kt(const float k) { kt = k; }

inline void PerfectTransmitter::set_ior(const float eta) { ior = eta; }

#endif
