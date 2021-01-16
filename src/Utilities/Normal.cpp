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

#include <math.h>

#include "Normal.h"



Normal::Normal(void)
	 : x(0.0), y(0.0), z(0.0)							
{}



Normal::Normal(double a)
	 : x(a), y(a), z(a)							
{}



Normal::Normal(double _x, double _y, double _z)	 
	: x(_x), y(_y), z(_z)
{}



Normal::Normal(const Normal& n)
	: x(n.x), y(n.y), z(n.z)
{}


Normal::Normal(const Vector3D& v)	 
	: x(v.x), y(v.y), z(v.z)  
{}



Normal::~Normal (void) 							
{}


Normal& 
Normal::operator= (const Normal& rhs) {
	if (this == &rhs) {
		return (*this);
	}

	x = rhs.x; y = rhs.y; z = rhs.z;

	return (*this);
}


Normal& 
Normal::operator= (const Vector3D& rhs) {
	x = rhs.x; y = rhs.y; z = rhs.z;
	return (*this);
}


Normal& 
Normal::operator= (const Point3D& rhs) {		
	x = rhs.x; y = rhs.y; z = rhs.z;
	return (*this);
}



void 													
Normal::normalize(void) {	
	double length = sqrt(x * x + y * y + z * z);
	x /= length; y /= length; z /= length;
}



// a normal is transformed by multiplying it on the left by the transpose of the upper left 3 x 3
// partition of the inverse transformation matrix

Normal 											
operator* (const Matrix& mat, const Normal& n) {
	return (Normal(	mat.m[0][0] * n.x + mat.m[1][0] * n.y + mat.m[2][0] * n.z,
					mat.m[0][1] * n.x + mat.m[1][1] * n.y + mat.m[2][1] * n.z,
					mat.m[0][2] * n.x + mat.m[1][2] * n.y + mat.m[2][2] * n.z));
}




