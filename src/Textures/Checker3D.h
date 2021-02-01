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

#ifndef __CHECKER3D__
#define __CHECKER3D__

#include "Texture.h"

class Checker3D : public Texture
{
public:
    Checker3D(void);
    Checker3D(const Checker3D& sc);

    Checker3D&
    operator= (const Checker3D& rhs);

    virtual Checker3D*
    clone(void) const;

    virtual
    ~Checker3D(void);

    virtual RGBColor
    get_color(const ShadeRec& sr) const;

    void
    set_size(const float s);

    void
    set_color1(const RGBColor& c);

    void
    set_color1(const float r, const float g, const float b);

    void
    set_color2(const RGBColor& c);

    void
    set_color2(const float r, const float g, const float b);

protected:
    RGBColor color1;
    RGBColor color2;
    float size;
};

inline void
Checker3D::set_size(const float s) {
    size = s;
}

inline void
Checker3D::set_color1(const RGBColor &c) {
    color1 = c;
}

inline void
Checker3D::set_color1(const float r, const float g, const float b) {
    color1.r = r; color1.g = g; color1.b = b;
}

inline void
Checker3D::set_color2(const RGBColor &c) {
    color2 = c;
}

inline void
Checker3D::set_color2(const float r, const float g, const float b) {
    color2.r = r; color2.g = g; color2.b = b;
}

#endif
