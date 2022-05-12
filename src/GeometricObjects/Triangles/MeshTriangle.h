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

#ifndef __MESH_TRIANGLE__
#define __MESH_TRIANGLE__

// This file contains the declaration of the class MeshTriangle
// Triangle classes derived from MeshTriangle, such as FlatMeshTriangle and SmoothMeshTriangle,
// are stored in a regular grid for rendering triangle meshes
// A mesh triangle stores integer indices into the vertices array in a Mesh object
// A mesh triangle also stores a pointer to the Mesh object
// A mesh triangle also stores the normal for use in FlatMeshTriangle and for
// computing the average normal at each vertex for SmoothMeshTriangles
// A mesh triangle defines the shadow hit function because this is independent of whether the
// triangle is flat shaded or smooth shaded or uv mapped or not uv mapped

// MeshTriangle doesn't inherit from the Triangle class discussed in Chapter 19,
// because Triangle stores the vertices and a normal

#include "../GeometricObject.h"
#include "../Mesh.h"

class MeshTriangle : public GeometricObject {
public:

    MeshTriangle(void) = default;

    explicit MeshTriangle(Mesh* _mesh_ptr, const int i1, const int i2, const int i3);

    virtual ~MeshTriangle(void);

    MeshTriangle(const MeshTriangle& mt);

    MeshTriangle(MeshTriangle&& mt) noexcept;

    MeshTriangle& operator=(const MeshTriangle& rhs);

    MeshTriangle& operator=(MeshTriangle&& rhs) noexcept;

    virtual MeshTriangle* clone(void) const = 0;

    virtual bool hit(const Ray& ray, float& tmin, ShadeRec& sr) const = 0;

    bool shadow_hit(const Ray& ray, float& tmin) const override;

    void compute_normal(const bool reverse_normal);

    virtual Normal get_normal(void) const override;

    virtual BBox get_bounding_box(void);

protected:

    Mesh* mesh_ptr = nullptr;  // stores all the data
    int index0 = 0;            // indices into the vertices array in the mesh
    int index1 = 0;
    int index2 = 0;
    Normal normal = Normal();
    float area = 0.0f;  // required for translucency

    float interpolate_u(const float beta, const float gamma) const;

    float interpolate_v(const float beta, const float gamma) const;
};

#endif
