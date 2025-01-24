//  Copyright (C) Kevin Suffern 2000-2007.
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.
//  See the file COPYING.txt for the full license.

//  Copyright notice for changes since the originally published version:
//  Copyright (C) Eduárd Mándy 2019-2025
//  Though this C++ code was change in a large measure it still has the original copyright notice.
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.
//  See the file COPYING.txt for the full license.

#include "BTDF.h"

#include "../Utilities/ShadeRec.h"
#include "../Utilities/Vector3D.h"

RGBColor BTDF::f(const ShadeRec& sr, const Vector3D& wo, const Vector3D& wi) const { return RGBColor::black; }

RGBColor BTDF::sample_f(const ShadeRec& sr, const Vector3D& wo, Vector3D& wi) const { return RGBColor::black; }

RGBColor BTDF::rho(const ShadeRec& sr, const Vector3D& wo) const { return RGBColor::black; }
