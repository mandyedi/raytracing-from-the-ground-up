#ifndef __PURE_RANDOM__
#define __PURE_RANDOM__

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

#include "Sampler.h"

class PureRandom : public Sampler {
public:

    PureRandom() = delete;

    explicit PureRandom(const int num);

    ~PureRandom() = default;

    PureRandom(const PureRandom& r) = default;

    PureRandom(PureRandom&& r) = default;

    PureRandom& operator=(const PureRandom& rhs) = default;

    PureRandom& operator=(PureRandom&& rhs) = default;

    virtual PureRandom* clone() const override;

private:

    virtual void generate_samples() override;
};

#endif
