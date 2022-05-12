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

#ifndef __TEXTURE__
#define __TEXTURE__

#include "../Utilities/RGBColor.h"
#include "../Utilities/ShadeRec.h"

class Texture {
public:

    Texture(void) = default;

    virtual ~Texture(void);

    Texture(const Texture& t);

    Texture(Texture&& t) noexcept;

    Texture& operator=(const Texture& t);

    Texture& operator=(Texture&& t) noexcept;

    virtual Texture* clone(void) const = 0;

    virtual RGBColor get_color(const ShadeRec& sr) const = 0;
};

#endif
