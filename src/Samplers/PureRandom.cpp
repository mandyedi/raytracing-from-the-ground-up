// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

//  Copyright notices for changes since the originally published version:
//  Copyright (C) Eduárd Mándy 2019-2021
//  Though this C++ code was change in a large measure it still has the original copyright notices.
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.
//  See the file COPYING.txt for the full license.

#include "PureRandom.h"
#include "../Utilities/Random.h"

// ---------------------------------------------------------------- default constructor
	
PureRandom::PureRandom(void)							
	: Sampler()
{}


// ---------------------------------------------------------------- constructor

PureRandom::PureRandom(const int num)
	: Sampler(num) {
	generate_samples();
}


// ---------------------------------------------------------------- constructor

PureRandom::PureRandom(const PureRandom& r)			
	: Sampler(r) {
	generate_samples();
}

// ---------------------------------------------------------------- assignment operator

PureRandom& 
PureRandom::operator= (const PureRandom& rhs) {
	if (this == &rhs) {
		return (*this);
	}
		
	Sampler::operator=(rhs);

	return (*this);
}

// ---------------------------------------------------------------- clone

PureRandom*										
PureRandom::clone(void) const {
	return (new PureRandom(*this));
}

// ---------------------------------------------------------------- destructor			

PureRandom::~PureRandom(void) {}


// ---------------------------------------------------------------- generate_samples	

void
PureRandom::generate_samples(void) {
	for (int p = 0; p < num_sets; p++) {
		for (int q = 0; q < num_samples; q++) {
			samples.push_back(Point2D(rand_float(), rand_float()));
		}
	}
}


