
#include <math.h>

#include "RGBColor.h"


RGBColor::RGBColor(void)
	: r(0.0), g(0.0), b(0.0) 							
{}



RGBColor::RGBColor(float c)
	: r(c), g(c), b(c) 							
{}
								


RGBColor::RGBColor(float _r, float _g, float _b)	
	: r(_r), g(_g), b(_b)
{}



RGBColor::RGBColor(const RGBColor& c)
	: r(c.r), g(c.g), b(c.b)
{} 				 
		


RGBColor::~RGBColor(void)		
{}



RGBColor& 											
RGBColor::operator= (const RGBColor& rhs) {
	if (this == &rhs) {
		return (*this);
	}

	r = rhs.r; g = rhs.g; b = rhs.b;

	return (*this);
}
 

// used for color filtering in Chapter 28

RGBColor
RGBColor::powc(float p) const {
	return (RGBColor(pow(r, p), pow(g, p), pow(b, p)));
}

const RGBColor RGBColor::black = RGBColor(0.0);
const RGBColor RGBColor::white = RGBColor(1.0);
const RGBColor RGBColor::red = RGBColor(1.0, 0.0, 0.0);
const RGBColor RGBColor::yellow = RGBColor(1, 1, 0);
const RGBColor RGBColor::brown = RGBColor(0.71, 0.40, 0.16);
const RGBColor RGBColor::darkGreen = RGBColor(0.0, 0.41, 0.41);
const RGBColor RGBColor::orange = RGBColor(1, 0.75, 0);
const RGBColor RGBColor::green = RGBColor(0, 0.6, 0.3);
const RGBColor RGBColor::lightGreen = RGBColor(0.65, 1, 0.30);
const RGBColor RGBColor::darkYellow = RGBColor(0.61, 0.61, 0);
const RGBColor RGBColor::lightPurple = RGBColor(0.65, 0.3, 1);
const RGBColor RGBColor::darkPurple = RGBColor(0.5, 0, 1);
const RGBColor RGBColor::grey = RGBColor(0.25);