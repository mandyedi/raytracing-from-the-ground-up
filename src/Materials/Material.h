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

#include "../Utilities/RGBColor.h"
#include "../Utilities/ShadeRec.h"
#include "../World/World.h"  // required for the shade function in all derived classes

class Material {
public:

    Material(void) = default;

    virtual ~Material(void);

    Material(const Material& material);

    Material(Material&& material) noexcept;

    Material& operator=(const Material& material);

    Material& operator=(Material&& material) noexcept;

    virtual Material* clone(void) const = 0;

    virtual RGBColor shade(ShadeRec& sr);

    virtual RGBColor path_shade(ShadeRec& sr);

    virtual RGBColor global_shade(ShadeRec& sr);

    // 18.6 Other Materials
    // It has to be defined for every material tha we want to render with area-light shading
    virtual RGBColor area_light_shade(ShadeRec& sr);

    virtual RGBColor get_Le(ShadeRec& sr) const;

protected:

    // From the book, chapter 16.7 Shadowing Options
    // Allows us to specify whether a material has shadows cast on it or not.
    // This is sometimes necessary for shading objects inside transparent objects
    // without having to render caustics (see Sections 28.7 and 28.8)
    bool shadows = true;
};

#endif
