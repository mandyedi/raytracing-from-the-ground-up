#ifndef __POINT_2D__
#define __POINT_2D__

class Point2D {	
	public:
	
		float	x, y;
				
	public:
	
		Point2D (void);
		Point2D (const float arg);
		Point2D (const float x1, const float y1);
		Point2D (const Point2D& p);
		~Point2D (void) {}

		Point2D&
		operator= (const Point2D& rhs);
		
		Point2D
		operator* (const float a);
};



inline Point2D
Point2D::operator* (const float a) {
	return (Point2D(a * x, a * y));
}


#endif


