#ifndef __MATHS__
#define __MATHS__

#include "Constants.h"

inline double
max(double x0, double x1);

inline double
max(double x0, double x1) {
	return((x0 > x1) ? x0 : x1);
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
