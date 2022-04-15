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

#ifndef __FISHEYE__
#define __FISHEYE__

#include "../Utilities/Point2D.h"
#include "../World/World.h"

class FishEye: public Camera {
    public:

        FishEye() = default;

        ~FishEye();

        FishEye(const FishEye& fe);

        FishEye(FishEye&& fe) noexcept;

        FishEye&
        operator= (const FishEye& fe);

        FishEye&
        operator= (FishEye&& fe) noexcept;

        Camera*
        clone(void) const override;

        Vector3D
        ray_direction(  const Point2D& pp,
                        const int   hres,
                        const int   vres,
                        const float s,
                        float&      r_squared) const;

        void
        render_scene(const World& w, float x = 0, int offset = 0) override;

        void
        set_fov(const float fov);

    private:

        float   psi_max = 120.0f;   // in degrees
};

inline void
FishEye::set_fov(const float fov)
{
    psi_max = fov / 2.0f;
}

#endif
