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

#ifndef __VIEW_PLANE__
#define __VIEW_PLANE__

class Sampler;

class ViewPlane {
	public:
		int 			hres;   					// horizontal image resolution 
		int 			vres;   					// vertical image resolution
		float			s;							// pixel size
		int				num_samples;				// number of samples per pixel
		
		float			gamma;						// gamma correction factor
		float			inv_gamma;					// the inverse of the gamma correction factor
		bool			show_out_of_gamut;			// display red if RGBColor out of gamut
		
		Sampler			*sampler_ptr;

		int				max_depth;
	
	public:
	
		ViewPlane();
				
		ViewPlane(const ViewPlane& vp);

		ViewPlane& operator= (const ViewPlane& rhs);
		
		~ViewPlane();

		void
		set_samples(const int n);

		void
		set_sampler(Sampler* sp);
						
		void 													
		set_hres(const int h_res);
		
		void 													
		set_vres(const int v_res);
				
		void
		set_pixel_size(const float size);
		
		void
		set_gamma(const float g);
		
		void
		set_gamut_display(const bool show);			

		void
		set_max_depth(int depth);
};





inline void 													
ViewPlane::set_hres(const int h_res) {
	hres = h_res;
}



inline void 													
ViewPlane::set_vres(const int v_res) {
	vres = v_res;
}



inline void 													
ViewPlane::set_pixel_size(const float size) {
	s = size;
}



inline void
ViewPlane::set_gamma(const float g) {
	gamma = g;
	inv_gamma = 1.0f / gamma;
}



inline void
ViewPlane::set_gamut_display(const bool show) {
	show_out_of_gamut = show;
}

inline void
ViewPlane::set_max_depth(int depth) {
	max_depth = depth;
}

#endif