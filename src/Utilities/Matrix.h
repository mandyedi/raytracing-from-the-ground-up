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

#ifndef __MATRIX__
#define __MATRIX__


class Matrix {
	
	public:
	
		double	m[4][4];
	
		
		Matrix(void);

		Matrix(const Matrix& mat);
		
		~Matrix (void);
			
		Matrix&
		operator= (const Matrix& rhs);
			
		Matrix
		operator* (const Matrix& mat) const;

		Matrix
		operator/ (const double d);

		void
		set_identity(void);
};


#endif


