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

#include "Phong.h"

class PerfectSpecular;
class PerfectTransmitter;

class Transparent : public Phong {
public:

    Transparent();

    ~Transparent();

    Transparent(const Transparent& gs);

    Transparent(Transparent&& gs) noexcept;

    Transparent& operator=(const Transparent& gs);

    Transparent& operator=(Transparent&& gs) noexcept;

    Transparent* clone() const override;

    RGBColor shade(ShadeRec& sr) override;

private:

    PerfectSpecular* reflective_brdf;
    PerfectTransmitter* specular_btdf;
};
