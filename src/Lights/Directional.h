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

#ifndef __DIRECTIONAL__
#define __DIRECTIONAL__

#include "../Utilities/RGBColor.h"
#include "../Utilities/ShadeRec.h"
#include "../Utilities/Vector3D.h"
#include "../World/World.h"  // you will need this later on for shadows
#include "Light.h"

class Directional : public Light {
public:

    Directional() = default;

    ~Directional();

    Directional(const Directional& d);

    Directional(Directional&& d) noexcept;

    Directional& operator=(const Directional& d);

    Directional& operator=(Directional&& d) noexcept;

    virtual Light* clone() const override;

    void scale_radiance(const float b);

    void set_color(const float c);

    void set_color(const RGBColor& c);

    void set_color(const float r, const float g, const float b);

    void set_direction(const Vector3D& d);

    void set_direction(float dx, float dy, float dz);

    virtual Vector3D get_direction(ShadeRec& sr) override;

    virtual RGBColor L(ShadeRec& sr) override;

    virtual bool in_shadow(const Ray& ray, const ShadeRec& sr) const;

private:

    float ls = 1.0f;
    RGBColor color = RGBColor::white;
    Vector3D dir = Vector3D(0.0f, 1.0f, 0.0f);  // direction the light comes from
};

inline void Directional::scale_radiance(const float b) { ls = b; }

inline void Directional::set_color(const float c) {
    color.r = c;
    color.g = c;
    color.b = c;
}

inline void Directional::set_color(const RGBColor& c) { color = c; }

inline void Directional::set_color(const float r, const float g, const float b) {
    color.r = r;
    color.g = g;
    color.b = b;
}

inline void Directional::set_direction(const Vector3D& d) {
    dir = d;
    dir.normalize();
}

inline void Directional::set_direction(float dx, float dy, float dz) {
    dir.x = dx;
    dir.y = dy;
    dir.z = dz;
    dir.normalize();
}

#endif
