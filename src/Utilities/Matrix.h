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


