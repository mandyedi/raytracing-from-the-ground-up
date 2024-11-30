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

#ifndef __FLAT_UV_MESH_TRIANGLE__
#define __FLAT_UV_MESH_TRIANGLE__

#include "MeshTriangle.h"

class FlatUVMeshTriangle : public MeshTriangle {
public:

    FlatUVMeshTriangle() = default;

    explicit FlatUVMeshTriangle(Mesh* _meshPtr, const int i0, const int i1, const int i2);

    ~FlatUVMeshTriangle() = default;

    FlatUVMeshTriangle(const FlatUVMeshTriangle& fmt) = default;
    FlatUVMeshTriangle(FlatUVMeshTriangle&& fmt) = default;
    FlatUVMeshTriangle& operator=(const FlatUVMeshTriangle& rhs) = default;
    FlatUVMeshTriangle& operator=(FlatUVMeshTriangle&& rhs) = default;

    FlatUVMeshTriangle* clone() const override;

    bool hit(const Ray& ray, float& tmin, ShadeRec& sr) const override;
};

#endif
