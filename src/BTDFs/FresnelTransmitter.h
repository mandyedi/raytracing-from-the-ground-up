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

#ifndef __FRESNEL_TRANSMITTER__
#define __FRESNEL_TRANSMITTER__

#include "BTDF.h"

class FresnelTransmitter : public BTDF {
public:

    FresnelTransmitter() = default;

    ~FresnelTransmitter() = default;

    FresnelTransmitter(const FresnelTransmitter& pt);

    FresnelTransmitter(FresnelTransmitter&& pt) noexcept;

    FresnelTransmitter& operator=(const FresnelTransmitter& rhs);

    FresnelTransmitter& operator=(FresnelTransmitter&& rhs) noexcept;

    FresnelTransmitter* clone() const override;

    void set_eta_in(const float eta);

    void set_eta_out(const float eta);

    bool tir(const ShadeRec& sr) const;

    RGBColor f(const ShadeRec& sr, const Vector3D& wo, const Vector3D& wi) const override;

    RGBColor sample_f(const ShadeRec& sr, const Vector3D& wo, Vector3D& wt) const override;
    
    RGBColor rho(const ShadeRec& sr, const Vector3D& wo) const override;

private:

    float eta_in = 1.0f;
    float eta_out = 1.0f;
    float kt = 0.0f; // TODO: what is kt?
    float ior = 0.0f; // TODO: what is ior?
};

inline void FresnelTransmitter::set_eta_in(const float eta) { eta_in = eta; }

inline void FresnelTransmitter::set_eta_out(const float eta) { eta_out = eta; }

#endif
