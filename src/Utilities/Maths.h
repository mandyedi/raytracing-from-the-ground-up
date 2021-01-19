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

#ifndef __MATHS__
#define __MATHS__

#include "Constants.h"

inline double
max(double x0, double x1);

inline double
max(double x0, double x1) {
	return((x0 < x1) ? x0 : x1);
}

inline float
max(float x0, float x1);

inline float
max(float x0, float x1) {
	return((x0 > x1) ? x0 : x1);
}

inline float
degreeToRadian(float degree) {
	return degree * PI_ON_180;
}

inline float
radianToDegree(float radian) {
	return radian * (180.0f * invPI);

}

#endif
