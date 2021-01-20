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

#ifndef __VECTOR_3D__
#define __VECTOR_3D__


#include "Matrix.h"

class Normal;
class Point3D;


class Vector3D {
	public:
	
		double	x, y, z;

	public:
	
		Vector3D(void);
		explicit Vector3D(double a);
		Vector3D(double _x, double _y, double _z);
		Vector3D(const Vector3D& v);
		explicit Vector3D(const Normal& n);
		explicit Vector3D(const Point3D& p);

		~Vector3D (void);

		Vector3D&
		operator= (const Vector3D& rhs);
		
		Vector3D&
		operator= (const Normal& rhs);
		
		Vector3D&
		operator= (const Point3D& rhs);
		
		Vector3D
		operator- (void) const;
				
		double
		length(void);
		
		double
		len_squared(void);
		
		Vector3D
		operator* (const double a) const;
				
		Vector3D
		operator/ (const double a) const;
		
		Vector3D
		operator+ (const Vector3D& v) const;
		
		Vector3D&
		operator+= (const Vector3D& v);
		
		Vector3D
		operator- (const Vector3D& v) const;
		
		double
		operator* (const Vector3D& b) const;
		
		Vector3D
		operator^ (const Vector3D& v) const;
		
		void
		normalize(void);
		
		Vector3D&
		hat(void);
};



// this does not change the current vector
// this allows ShadeRec objects to be declared as constant arguments in many shading
// functions that reverse the direction of a ray that's stored in the ShadeRec object

inline Vector3D 
Vector3D::operator- (void) const {
	return (Vector3D(-x, -y, -z));    
}



inline double													
Vector3D::len_squared(void) {	
	return (x * x + y * y + z * z);
}



inline Vector3D
Vector3D::operator* (const double a) const {	
	return (Vector3D(x * a, y * a, z * a));	
}


inline Vector3D
Vector3D::operator/ (const double a) const {	
	return (Vector3D(x / a, y / a, z / a));	
}



inline Vector3D
Vector3D::operator+ (const Vector3D& v) const {
	return (Vector3D(x + v.x, y + v.y, z + v.z));
}



inline Vector3D
Vector3D::operator- (const Vector3D& v) const {
	return (Vector3D(x - v.x, y - v.y, z - v.z));
}



inline double 
Vector3D::operator* (const Vector3D& v) const {
	return (x * v.x + y * v.y + z * v.z);
} 



inline Vector3D 									
Vector3D::operator^ (const Vector3D& v) const {
	return (Vector3D(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x));
}



inline Vector3D& 
Vector3D::operator+= (const Vector3D& v) {
	x += v.x; y += v.y; z += v.z;
	return (*this);
}






Vector3D 
operator* (const double a, const Vector3D& v);

inline Vector3D 
operator* (const double a, const Vector3D& v) {
	return (Vector3D(a * v.x, a * v.y, a * v.z));	
}





Vector3D 
operator* (const Matrix& mat, const Vector3D& v);


#endif


