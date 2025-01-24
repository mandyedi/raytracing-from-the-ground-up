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

#ifndef __LIGHT__
#define __LIGHT__

#include "../Utilities/RGBColor.h"
#include "../Utilities/Ray.h"
#include "../Utilities/Vector3D.h"

class ShadeRec;

class Light {
public:

    Light() = default;

    virtual ~Light();

    Light(const Light& ls);

    Light(Light&& ls) noexcept;

    Light& operator=(const Light& rhs);

    Light& operator=(Light&& rhs) noexcept;

    virtual Light* clone() const = 0;

    virtual Vector3D get_direction(ShadeRec& sr) = 0;

    virtual RGBColor L(ShadeRec& sr);

    virtual bool in_shadow(const Ray& ray, const ShadeRec& sr) const;

    virtual float G(const ShadeRec& sr) const;

    virtual float pdf(const ShadeRec& sr) const;

    void set_shadows(bool _shadows);

    bool casts_shadows();

protected:

    bool shadows = false;
};

inline void Light::set_shadows(bool _shadows) { shadows = _shadows; }

inline bool Light::casts_shadows() { return shadows; }

#endif