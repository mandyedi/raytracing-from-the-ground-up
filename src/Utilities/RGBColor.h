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
	return (0.333333333333 * (r + g + b));
}





RGBColor 
operator* (const float a, const RGBColor& c);

inline RGBColor 
operator* (const float a, const RGBColor& c) {
	return (RGBColor (a * c.r, a * c.g, a * c.b));	
}


#endif
