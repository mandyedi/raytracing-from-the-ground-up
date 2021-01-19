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

#ifndef __POINT3D__
#define __POINT3D__


#include "Matrix.h"
#include "Vector3D.h"

class Point3D {
	public:
	
		double x, y, z;
	
		Point3D();
		Point3D(const double a);
		Point3D(const double a, const double b, const double c);
		Point3D(const Point3D& p);
		~Point3D();
		
		Point3D&
		operator= (const Point3D& p);
		
		Point3D
		operator- (void) const;
	
		Vector3D
		operator- (const Point3D& p) const;
		
		Point3D
		operator+ (const Vector3D& v) const;
		
		Point3D
		operator- (const Vector3D& v) const;
				
		Point3D
		operator* (const double a) const;
		
		double
		d_squared(const Point3D& p) const;
		
		double
		distance(const Point3D& p) const;
};




inline Point3D 
Point3D::operator- (void) const {
	return (Point3D(-x, -y, -z));
}


inline Vector3D 
Point3D::operator- (const Point3D& p) const {
	return (Vector3D(x - p.x,y - p.y,z - p.z));
}


inline Point3D 
Point3D::operator+ (const Vector3D& v) const {
	return (Point3D(x + v.x, y + v.y, z + v.z));
}


inline Point3D 
Point3D::operator- (const Vector3D& v) const {
	return (Point3D(x - v.x, y - v.y, z - v.z));
}


inline Point3D 
Point3D::operator* (const double a) const {
	return (Point3D(x * a,y * a,z * a));
}


inline double
Point3D::d_squared(const Point3D& p) const {
	return (	(x - p.x) * (x - p.x) 
			+ 	(y - p.y) * (y - p.y)
			+	(z - p.z) * (z - p.z) );
}





Point3D
operator* (double a, const Point3D& p);

inline Point3D
operator* (double a, const Point3D& p) {
	return (Point3D(a * p.x, a * p.y, a * p.z));
}




Point3D 						
operator* (const Matrix& mat, const Point3D& p);

#endif
