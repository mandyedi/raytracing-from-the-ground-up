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

#include "ViewPlane.h"
#include "../Samplers/Sampler.h"
#include "../Samplers/MultiJittered.h"
#include "../Samplers/Regular.h"

ViewPlane::ViewPlane(void)							
	: 	hres(400), 
		vres(400),
		s(1.0),
		num_samples(1),
		gamma(1.0),
		inv_gamma(1.0),
		show_out_of_gamut(false),
		sampler_ptr(nullptr)
{}



ViewPlane::ViewPlane(const ViewPlane& vp)   
	:  	hres(vp.hres),  
		vres(vp.vres), 
		s(vp.s),
		num_samples(vp.num_samples),
		gamma(vp.gamma),
		inv_gamma(vp.inv_gamma),
		show_out_of_gamut(vp.show_out_of_gamut)
{
	if (vp.sampler_ptr) {
		sampler_ptr = vp.sampler_ptr->clone();
	}
	else {
		sampler_ptr = nullptr;
	}
}



ViewPlane& 
ViewPlane::operator= (const ViewPlane& rhs) {
	if (this == &rhs) {
		return (*this);
	}
		
	hres 				= rhs.hres;
	vres 				= rhs.vres;
	s					= rhs.s;
	num_samples			= rhs.num_samples;
	gamma				= rhs.gamma;
	inv_gamma			= rhs.inv_gamma;
	show_out_of_gamut	= rhs.show_out_of_gamut;

	if (sampler_ptr) {
		delete sampler_ptr;
		sampler_ptr = nullptr;
	}

	if (rhs.sampler_ptr) {
		sampler_ptr = rhs.sampler_ptr->clone();
	}
	
	return (*this);
}



ViewPlane::~ViewPlane(void) {
	if (sampler_ptr) {
		delete sampler_ptr;
		sampler_ptr = nullptr;
	}
}

void
ViewPlane::set_samples(const int n) {
	num_samples = n;
	
	if (sampler_ptr) {
		delete sampler_ptr;
		sampler_ptr = nullptr;
	}
	
	if (num_samples > 1) {
		sampler_ptr = new MultiJittered(num_samples);
	}
	else {
		sampler_ptr = new Regular(1);
	}
}

void
ViewPlane::set_sampler(Sampler* sp) {
	
	if (sampler_ptr) {
		delete sampler_ptr;
		sampler_ptr = nullptr;
	}
	
	num_samples = sp->get_num_samples();
	sampler_ptr = sp;
}