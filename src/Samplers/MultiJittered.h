#ifndef __MULTI_JITTERED__
#define __MULTI_JITTERED__

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

class MultiJittered : public Sampler {
public:

    MultiJittered() = default;

    explicit MultiJittered(const int num_samples);

    explicit MultiJittered(const int num_samples, const int m);

    ~MultiJittered() = default;

    MultiJittered(const MultiJittered& r) = default;

    MultiJittered(MultiJittered&& r) = default;

    MultiJittered& operator=(const MultiJittered& rhs) = default;

    MultiJittered& operator=(MultiJittered&& rhs) = default;

    virtual MultiJittered* clone() const override;

private:

    virtual void generate_samples() override;
};

#endif
