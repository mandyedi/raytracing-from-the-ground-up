
#include <math.h>

#include "RGBColor.h"


RGBColor::RGBColor(void)
	: r(0.0f), g(0.0f), b(0.0f) 							
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
	return (RGBColor(powf(r, p), powf(g, p), powf(b, p)));
}

const RGBColor RGBColor::black = RGBColor(0.0f);
const RGBColor RGBColor::white = RGBColor(1.0f);
const RGBColor RGBColor::red = RGBColor(1.0f, 0.0f, 0.0f);
const RGBColor RGBColor::yellow = RGBColor(1.0f, 1.0f, 0.0f);
const RGBColor RGBColor::brown = RGBColor(0.71f, 0.4f, 0.16f);
const RGBColor RGBColor::darkGreen = RGBColor(0.0f, 0.41f, 0.0f);
const RGBColor RGBColor::orange = RGBColor(1.0f, 0.75, 0.0f);
const RGBColor RGBColor::green = RGBColor(0.0f, 0.6f, 0.3f);
const RGBColor RGBColor::lightGreen = RGBColor(0.65f, 1.0f, 0.3f);
const RGBColor RGBColor::darkYellow = RGBColor(0.61f, 0.61f, 0.0f);
const RGBColor RGBColor::lightPurple = RGBColor(0.65f, 0.3f, 1.0f);
const RGBColor RGBColor::darkPurple = RGBColor(0.5f, 0.0f, 1.0f);
const RGBColor RGBColor::grey = RGBColor(0.25f);