#ifndef __HAMMERSLEY__
#define __HAMMERSLEY__


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

#include "Sampler.h"

class Hammersley: public Sampler {
    public:

        Hammersley(void) = delete;

        explicit Hammersley(const int num);

        ~Hammersley(void) = default;

        Hammersley(const Hammersley& r)  = default;

        Hammersley(Hammersley&& r) = default;

        Hammersley&
        operator= (const Hammersley& rhs) = default;

        Hammersley&
        operator= (Hammersley&& rhs) = default;

        virtual Hammersley*
        clone(void) const override;

        double
        phi(int j);

    private:

        virtual void
        generate_samples(void) override;
};

#endif

