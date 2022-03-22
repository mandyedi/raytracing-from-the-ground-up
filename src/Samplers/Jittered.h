#ifndef __JITTERED__
#define __JITTERED__


// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

//  Copyright notice for changes since the originally published version:
//  Copyright (C) Eduárd Mándy 2019-2021
//  Though this C++ code was change in a large measure it still has the original copyright notice.
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.
//  See the file COPYING.txt for the full license.


#include "Sampler.h"

class Jittered: public Sampler {
	public:
		
		Jittered(void) = delete;
		
		explicit Jittered(const int num_samples);					
		
		explicit Jittered(const int num_samples, const int m);

		Jittered(const Jittered& r)  = default;

		Jittered(Jittered&& r) = default;

		Jittered& 
		operator= (const Jittered& rhs) = default;

		Jittered& 
		operator= (Jittered&& rhs) = default;

		virtual
		~Jittered(void);

		virtual Jittered*								
		clone(void) const override;							
		
	private:
		
		virtual void									
		generate_samples(void) override;
};

#endif

