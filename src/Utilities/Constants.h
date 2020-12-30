#ifndef __CONSTANTS__
#define __CONSTANTS__

#include "RGBColor.h"

const float 	PI 			= 3.1415926535897932384;
const float 	TWO_PI 		= 6.2831853071795864769;
const float 	PI_ON_180 	= 0.0174532925199432957;
const float 	invPI 		= 0.3183098861837906715;
const float 	invTWO_PI 	= 0.1591549430918953358;

const float 	kEpsilon 	= 0.0001; 
const float		kHugeValue	= 1.0E10;

// TODO(fix) move colors to RGBColor
const RGBColor black(0.0);
const RGBColor white(1.0);
const RGBColor red(1.0, 0.0, 0.0);
const RGBColor yellow(1, 1, 0);
const RGBColor brown(0.71, 0.40, 0.16);
const RGBColor darkGreen(0.0, 0.41, 0.41);
const RGBColor orange(1, 0.75, 0);
const RGBColor green(0, 0.6, 0.3);
const RGBColor lightGreen(0.65, 1, 0.30);
const RGBColor darkYellow(0.61, 0.61, 0);
const RGBColor lightPurple(0.65, 0.3, 1);
const RGBColor darkPurple(0.5, 0, 1);
const RGBColor grey(0.25);

#endif
