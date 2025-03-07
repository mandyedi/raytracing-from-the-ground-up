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

#ifndef __FLAT_MESH_TRIANGLE__
#define __FLAT_MESH_TRIANGLE__

// FlatMeshTriangle is a MeshTriangle that uses flat shading with a constant normal
// This uses the inherited shadow hit function from MeshTriangle

#include "MeshTriangle.h"

class FlatMeshTriangle : public MeshTriangle {
public:

    FlatMeshTriangle() = default;

    explicit FlatMeshTriangle(Mesh* _meshPtr, const int i0, const int i1, const int i2);

    ~FlatMeshTriangle() = default;

    FlatMeshTriangle(const FlatMeshTriangle& fmt) = default;
    FlatMeshTriangle(FlatMeshTriangle&& fmt) = default;
    FlatMeshTriangle& operator=(const FlatMeshTriangle& rhs) = default;
    FlatMeshTriangle& operator=(FlatMeshTriangle&& rhs) = default;

    FlatMeshTriangle* clone() const override;

    bool hit(const Ray& ray, float& tmin, ShadeRec& sr) const override;
};

#endif
