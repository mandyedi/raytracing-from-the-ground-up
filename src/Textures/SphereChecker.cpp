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

#include <cmath>

#include "SphereChecker.h"
#include "../Utilities/Constants.h"

SphereChecker* SphereChecker::clone(void) const {
    return new SphereChecker(*this);
}

RGBColor SphereChecker::get_color(const ShadeRec& sr) const {
    float x = sr.local_hit_point.x;
    float y = sr.local_hit_point.y;
    float z = sr.local_hit_point.z;

    float theta = acos(y);
    float phi   = atan2(x, z);
    if (phi < 0.0f) {
        phi += 2.0f * PI;
    }

    float phi_size = 2.0 * PI / num_horizontal_checkers;       // in radians - azimuth angle
    float theta_size = PI / num_vertical_checkers;           // in radians - polar angle
    
    float i_phi = floor(phi / phi_size);
    float i_theta = floor(theta / theta_size);
    
    float f_phi     = phi / phi_size - static_cast<float>(i_phi);
    float f_theta     = theta / theta_size - static_cast<float>(i_theta);
    
    float phi_line_width = 0.5f * vertical_line_width;
    float theta_line_width = 0.5f * horizontal_line_width;
    
    bool in_outline = (f_phi < phi_line_width || f_phi > 1.0f - phi_line_width) ||
                      (f_theta < theta_line_width || f_theta > 1.0f - theta_line_width);
    
    if ((static_cast<int>(i_phi) + static_cast<int>(i_theta)) % 2 == 0) {
        if (!in_outline) {
            return (color1);
        }
    }
    else {
        if (!in_outline) {
            return (color2);
        }
    }
    
    return line_color;
}
