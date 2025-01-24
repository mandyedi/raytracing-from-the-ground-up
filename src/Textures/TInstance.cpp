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

#include <cmath>

#include "TInstance.h"
#include "../Utilities/Constants.h"

// Note: One line is different here from Listing 30.7.
// There is no *= operator implemented for multiplying a Point3D by a 
// Matrix on the left.
// The notation below is consistent with Instance.cpp which uses, for example,
// inv_ray.d = inv_matrix * inv_ray.d;
RGBColor TInstance::get_color(const ShadeRec& sr) const {
    // TODO: ShadeRec copy constructor is not implemented, it contains a Material pointer!
    ShadeRec local_sr(sr);
    local_sr.local_hit_point = inv_matrix * local_sr.local_hit_point;

    return (texture_ptr->get_color(local_sr));
}

void
TInstance::translate(const float dx, const float dy, const float dz)
{
    Matrix inv_translation_matrix;

    inv_translation_matrix.m[0][3] = -dx;
    inv_translation_matrix.m[1][3] = -dy;
    inv_translation_matrix.m[2][3] = -dz;

    inv_matrix = inv_matrix * inv_translation_matrix;
}

void TInstance::scale(const float sx, const float sy, const float sz) {
    Matrix inv_scaling_matrix;

    inv_scaling_matrix.m[0][0] = 1.0f / sx;
    inv_scaling_matrix.m[1][1] = 1.0f / sy;
    inv_scaling_matrix.m[2][2] = 1.0f / sz;

    inv_matrix = inv_matrix * inv_scaling_matrix;
}

void
TInstance::rotate_x(const float theta)
{
    float sin_theta = sin(theta * PI_ON_180);
    float cos_theta = cos(theta * PI_ON_180);

    Matrix inv_x_rotation_matrix;

    inv_x_rotation_matrix.m[1][1] = cos_theta;
    inv_x_rotation_matrix.m[1][2] = sin_theta;
    inv_x_rotation_matrix.m[2][1] = -sin_theta;
    inv_x_rotation_matrix.m[2][2] = cos_theta;

    inv_matrix = inv_matrix * inv_x_rotation_matrix;
}

void
TInstance::rotate_y(const float theta)
{
    float sin_theta = sin(theta * PI / 180.0f);
    float cos_theta = cos(theta * PI / 180.0f);

    Matrix inv_y_rotation_matrix;

    inv_y_rotation_matrix.m[0][0] = cos_theta;
    inv_y_rotation_matrix.m[0][2] = -sin_theta;
    inv_y_rotation_matrix.m[2][0] = sin_theta;
    inv_y_rotation_matrix.m[2][2] = cos_theta;

    inv_matrix = inv_matrix * inv_y_rotation_matrix;
}

void
TInstance::rotate_z(const float theta)
{
    float sin_theta = sin(theta * PI / 180.0f);
    float cos_theta = cos(theta * PI / 180.0f);

    Matrix inv_z_rotation_matrix;

    inv_z_rotation_matrix.m[0][0] = cos_theta;
    inv_z_rotation_matrix.m[0][1] = sin_theta;
    inv_z_rotation_matrix.m[1][0] = -sin_theta;
    inv_z_rotation_matrix.m[1][1] = cos_theta;

    inv_matrix = inv_matrix * inv_z_rotation_matrix;
}

void
TInstance::shear(const Matrix &s)
{
    Matrix inverse_shearing_matrix;

    float discriminant = 1.0f - s.m[1][0] * s.m[0][1] - s.m[2][0] * s.m[0][2] - s.m[2][1] * s.m[1][2]
        + s.m[1][0] * s.m[2][1] * s.m[0][2] + s.m[2][0] * s.m[0][1] * s.m[2][1];

    // diagonals
    inverse_shearing_matrix.m[0][0] = 1.0f - s.m[2][1] * s.m[1][2];
    inverse_shearing_matrix.m[1][1] = 1.0f - s.m[2][0] * s.m[0][2];
    inverse_shearing_matrix.m[2][2] = 1.0f - s.m[1][0] * s.m[0][1];
    inverse_shearing_matrix.m[3][3] = discriminant;

    // first row
    inverse_shearing_matrix.m[0][1] = -s.m[1][0] + s.m[2][0] * s.m[1][2];
    inverse_shearing_matrix.m[0][2] = -s.m[2][0] + s.m[1][0] * s.m[2][1];

    // second row
    inverse_shearing_matrix.m[1][0] = -s.m[0][1] + s.m[2][1] * s.m[0][2];
    inverse_shearing_matrix.m[1][2] = -s.m[2][1] + s.m[2][0] * s.m[0][1];

    // third row
    inverse_shearing_matrix.m[2][0] = -s.m[0][2] + s.m[0][1] * s.m[1][2];
    inverse_shearing_matrix.m[2][1] = -s.m[1][2] + s.m[1][0] * s.m[0][2];

    // divide by discriminant
    inverse_shearing_matrix = inverse_shearing_matrix / discriminant;
    inv_matrix = inv_matrix * inverse_shearing_matrix;
}