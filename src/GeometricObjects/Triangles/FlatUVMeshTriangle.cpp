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

#include "FlatUVMeshTriangle.h"

#include <limits>

FlatUVMeshTriangle::FlatUVMeshTriangle(Mesh* _mesh_ptr, const int i0, const int i1, const int i2) : MeshTriangle(_mesh_ptr, i0, i1, i2) {}

FlatUVMeshTriangle* FlatUVMeshTriangle::clone() const { return new FlatUVMeshTriangle(*this); }

bool FlatUVMeshTriangle::hit(const Ray& ray, float& tmin, ShadeRec& sr) const {
    Point3D v0(mesh_ptr->vertices[index0]);
    Point3D v1(mesh_ptr->vertices[index1]);
    Point3D v2(mesh_ptr->vertices[index2]);

    float a = v0.x - v1.x, b = v0.x - v2.x, c = ray.d.x, d = v0.x - ray.o.x;
    float e = v0.y - v1.y, f = v0.y - v2.y, g = ray.d.y, h = v0.y - ray.o.y;
    float i = v0.z - v1.z, j = v0.z - v2.z, k = ray.d.z, l = v0.z - ray.o.z;

    float m = f * k - g * j, n = h * k - g * l, p = f * l - h * j;
    float q = g * i - e * k, s = e * j - f * i;

    float inv_denom = 1.0f / (a * m + b * q + c * s);

    float e1 = d * m - b * n - c * p;
    float beta = e1 * inv_denom;

    if (beta < 0.0f) {
        return false;
    }

    float r = e * l - h * i;
    float e2 = a * n + d * q + c * r;
    float gamma = e2 * inv_denom;

    if (gamma < 0.0f) {
        return false;
    }

    if (beta + gamma > 1.0f) {
        return false;
    }

    float e3 = a * p - b * r + d * s;
    float t = e3 * inv_denom;

    if (t < std::numeric_limits<float>::epsilon()) {
        return false;
    }

    tmin = t;
    sr.u = interpolate_u(beta, gamma);
    sr.v = interpolate_v(beta, gamma);

    // From the book, chapter 29.6 Triangle Meshes, page 663
    // Storing local hit point in ShadeRec object is not required here
    // because the function ImageTexture::get_color in Listing 29.7
    // doesn't use the local hit point when it uses u and v.

    return true;
}
