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

#ifndef __POINT_2D__
#define __POINT_2D__

class Point2D {
public:

    float x = 0.0f;
    float y = 0.0f;

    Point2D(void) = default;
    explicit Point2D(float arg);
    explicit Point2D(float x1, float y1);

    Point2D operator*(float a);
};

inline Point2D Point2D::operator*(float a) { return (Point2D(a * x, a * y)); }

#endif
