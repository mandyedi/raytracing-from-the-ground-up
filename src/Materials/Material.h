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

#ifndef __MATERIAL__
#define __MATERIAL__

#include "../World/World.h"			// required for the shade function in all derived classes
#include "../Utilities/RGBColor.h"
#include "../Utilities/ShadeRec.h"

class Material {	
	public:
	
		Material(void);						
		
		Material(const Material& material); 
		
		virtual Material*								
		clone(void) const = 0;	
				
		virtual 								
		~Material(void);
				
		virtual RGBColor
		shade(ShadeRec& sr);	
		
	protected:
	
		Material& 								
		operator= (const Material& rhs);

		// From the book, chapter 16.7 Shadowing Options
		// Allows us to specify whether a material has shadows cast on it or not.
		// This is sometimes necessary for shading objects inside transparent objects
		// without having to render caustics (see Sections 28.7 and 28.8)
		bool shadows;
};

#endif
