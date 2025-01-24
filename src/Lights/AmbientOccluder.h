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

#ifndef __AMBIENTOCCLUDER__
#define __AMBIENTOCCLUDER__

#include "../Utilities/Point3D.h"
#include "../Utilities/RGBColor.h"
#include "../Utilities/ShadeRec.h"
#include "../Utilities/Vector3D.h"
#include "../World/World.h"  // you will need this later on for shadows
#include "Light.h"

class Sampler;

class AmbientOccluder : public Light {
public:

    AmbientOccluder() = default;

    virtual ~AmbientOccluder();

    AmbientOccluder(const AmbientOccluder& a);

    AmbientOccluder(AmbientOccluder&& a) noexcept;

    AmbientOccluder& operator=(const AmbientOccluder& a);

    AmbientOccluder& operator=(AmbientOccluder&& a) noexcept;

    virtual Light* clone() const override;

    void set_sampler(Sampler* s_ptr);

    virtual Vector3D get_direction(ShadeRec& sr);

    virtual bool in_shadow(const Ray& ray, const ShadeRec& sr) const;

    virtual RGBColor L(ShadeRec& sr);

    void scale_radiance(const float s);

    void set_min_amount(const float f);

private:

    float ls = 1.0f;
    RGBColor color = RGBColor::white;
    float min_amount = 0.0f;
    Vector3D u = Vector3D(1.0f, 0.0f, 0.0f);
    Vector3D v = Vector3D(0.0f, 1.0f, 0.0f);
    Vector3D w = Vector3D(0.0f, 0.0f, 1.0f);
    Sampler* sampler_ptr = nullptr;
};

inline void AmbientOccluder::scale_radiance(const float s) { ls = s; }

inline void AmbientOccluder::set_min_amount(const float m) { min_amount = m; }

#endif