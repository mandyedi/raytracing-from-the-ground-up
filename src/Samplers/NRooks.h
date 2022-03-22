#ifndef __N_ROOKS__
#define __N_ROOKS__


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

class NRooks: public Sampler {
	public:

		NRooks(void) = delete;
		
		explicit NRooks(const int num_samples);					
		
		explicit NRooks(const int num_samples, const int m);	

		~NRooks(void) = default;					

		NRooks(const NRooks& r)  = default;

		NRooks(NRooks&& r) = default;

		NRooks& 
		operator= (const NRooks& rhs) = default;

		NRooks& 
		operator= (NRooks&& rhs) = default;

		virtual NRooks*								
		clone(void) const override;			

	private:
		
		virtual void									
		generate_samples(void) override;						
};

#endif

