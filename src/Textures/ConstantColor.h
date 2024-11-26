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

#ifndef __CONSTANTCOLOR__
#define __CONSTANTCOLOR__

#include "Texture.h"
#include "../Utilities/RGBColor.h"

class ConstantColor : public Texture {
public:

    void set_color(const RGBColor& c);

    RGBColor get_color(const ShadeRec& sr) const override;

private:

    RGBColor color = RGBColor::white;
};

inline void ConstantColor::set_color(const RGBColor &c) { color = c; }

#endif
