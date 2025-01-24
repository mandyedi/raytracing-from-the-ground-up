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

#ifndef __T_INSTANCE__
#define __T_INSTANCE__

#include "Texture.h"
#include "../Utilities/Matrix.h"

class ShadeRec;

class TInstance: public Texture {
public:

    void set_texture(Texture* t_ptr);

    RGBColor get_color(const ShadeRec& sr) const;

    void translate(const float dx, const float dy, const float dz);

    void scale(const float sx, const float sy, const float sz);

    void rotate_x(const float theta);

    void rotate_y(const float theta);

    void rotate_z(const float theta);

    void shear(const Matrix &s);

private:

    Texture* texture_ptr;
    Matrix inv_matrix;
};

inline void TInstance::set_texture(Texture *t_ptr) {
    texture_ptr = t_ptr;
}

#endif