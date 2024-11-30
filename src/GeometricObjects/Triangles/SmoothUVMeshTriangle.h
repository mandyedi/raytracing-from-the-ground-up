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

#ifndef __SMOOTH_UV_MESH_TRIANGLE__
#define __SMOOTH_UV_MESH_TRIANGLE__

#include "MeshTriangle.h"

class SmoothUVMeshTriangle : public MeshTriangle {
public:

    SmoothUVMeshTriangle() = default;

    explicit SmoothUVMeshTriangle(Mesh* _meshPtr, const int i0, const int i1, const int i2);

    ~SmoothUVMeshTriangle() = default;
    SmoothUVMeshTriangle(const SmoothUVMeshTriangle& fmt) = default;
    SmoothUVMeshTriangle(SmoothUVMeshTriangle&& fmt) = default;
    SmoothUVMeshTriangle& operator=(const SmoothUVMeshTriangle& rhs) = default;
    SmoothUVMeshTriangle& operator=(SmoothUVMeshTriangle&& rhs) = default;

    virtual SmoothUVMeshTriangle* clone() const override;

    virtual bool hit(const Ray& ray, float& tmin, ShadeRec& sr) const override;

protected:

    Normal interpolate_normal(const float beta, const float gamma) const;
};

#endif
