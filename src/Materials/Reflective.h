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

#ifndef __REFLECTIVE__
#define __REFLECTIVE__

#include "../BRDFs/PerfectSpecular.h"
#include "Phong.h"

class Reflective : public Phong {
public:

    Reflective() = default;

    ~Reflective();

    Reflective(const Reflective& rm);

    Reflective(Reflective&& rm) noexcept;

    Reflective& operator=(const Reflective& rhs);

    Reflective& operator=(Reflective&& rhs) noexcept;

    Reflective* clone() const override;

    void set_kr(const float k);

    void set_cr(const RGBColor& c);

    void set_cr(const float r, const float g, const float b);

    void set_cr(const float c);

    RGBColor shade(ShadeRec& s) override;

    RGBColor path_shade(ShadeRec& sr) override;

    RGBColor global_shade(ShadeRec& sr);

private:

    PerfectSpecular* reflective_brdf = new PerfectSpecular;
};

inline void Reflective::set_kr(const float k) { reflective_brdf->set_kr(k); }

inline void Reflective::set_cr(const RGBColor& c) { reflective_brdf->set_cr(c); }

inline void Reflective::set_cr(const float r, const float g, const float b) { reflective_brdf->set_cr(r, g, b); }

inline void Reflective::set_cr(const float c) { reflective_brdf->set_cr(c); }

#endif
