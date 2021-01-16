//  Copyright (C) Kevin Suffern 2000-2007.
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.
//  See the file COPYING.txt for the full license.

//  Copyright notices for changes since the originally published version:
//  Copyright (C) Eduárd Mándy 2019-2021
//  Though this C++ code was change in a large measure it still has the original copyright notices.
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.
//  See the file COPYING.txt for the full license.

#ifndef __RGB_COLOR__
#define __RGB_COLOR__



class RGBColor {
	
	public:
	
		float	r, g, b;									
				
	public:
	
		RGBColor(void);
		RGBColor(float c);
		RGBColor(float _r, float _g, float _b);
		RGBColor(const RGBColor& c);
		
		~RGBColor(void);
		
		RGBColor&
		operator= (const RGBColor& rhs);

		RGBColor
		operator+ (const RGBColor& c) const;

		RGBColor&
		operator+= (const RGBColor& c);
		
		RGBColor
		operator* (const float a) const;
		
		RGBColor&
		operator*= (const float a);
				
		RGBColor
		operator/ (const float a) const;
		
		RGBColor&
		operator/= (const float a);
				
		RGBColor
		operator* (const RGBColor& c) const;
		
		bool
		operator== (const RGBColor& c) const;

		RGBColor
		powc(float p) const;
		
		float
		average(void) const;

		/*static*/ static const RGBColor black;
		/*static*/ static const RGBColor white;
		/*static*/ static const RGBColor red;
		/*static*/ static const RGBColor yellow;
		/*static*/ static const RGBColor brown;
		/*static*/ static const RGBColor darkGreen;
		/*static*/ static const RGBColor orange;
		/*static*/ static const RGBColor green;
		/*static*/ static const RGBColor lightGreen;
		/*static*/ static const RGBColor darkYellow;
		/*static*/ static const RGBColor lightPurple;
		/*static*/ static const RGBColor darkPurple;
		/*static*/ static const RGBColor grey;
};




inline RGBColor 
RGBColor::operator+ (const RGBColor& c) const {
	return (RGBColor(r + c.r, g + c.g, b + c.b));
}


inline RGBColor& 
RGBColor::operator+= (const RGBColor& c) {
	r += c.r; g += c.g; b += c.b;
    return (*this);
}


inline RGBColor 
RGBColor::operator* (const float a) const {
	return (RGBColor (r * a, g * a, b * a));	
}


inline RGBColor& 
RGBColor::operator*= (const float a) {
	r *= a; g *= a; b *= a;
	return (*this);
}


inline RGBColor 
RGBColor::operator/ (const float a) const {
	return (RGBColor (r / a, g / a, b / a));
}


inline RGBColor& 
RGBColor::operator/= (const float a) {	
	r /= a; g /= a; b /= a;
	return (*this);
}



inline RGBColor 
RGBColor::operator* (const RGBColor& c) const {
	return (RGBColor (r * c.r, g * c.g, b * c.b));
} 


inline bool
RGBColor::operator== (const RGBColor& c) const {
	return (r == c.r && g == c.g && b == c.b);
}


inline float											
RGBColor::average(void) const {
	return (0.333333333333f * (r + g + b));
}





RGBColor 
operator* (const float a, const RGBColor& c);

inline RGBColor 
operator* (const float a, const RGBColor& c) {
	return (RGBColor (a * c.r, a * c.g, a * c.b));	
}


#endif
