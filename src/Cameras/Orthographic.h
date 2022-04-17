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

#ifndef __ORTHOGRAPHIC__
#define __ORTHOGRAPHIC__

#include "Camera.h"
#include "../Utilities/Point3D.h"

class World;


class Orthographic: public Camera {
    public:

        Orthographic() = default;

        ~Orthographic();

        Orthographic(const Orthographic& p);

        Orthographic(Orthographic&& p) noexcept;

        Orthographic&
        operator= (const Orthographic& p);

        Orthographic&
        operator= (Orthographic&& p) noexcept;

        Camera*
        clone(void) const override;

        void
        render_scene(const World& w, float x = 0.0f, int offset = 0) override;

    private:

        Point3D eye = Point3D(0.0f);
};

#endif
