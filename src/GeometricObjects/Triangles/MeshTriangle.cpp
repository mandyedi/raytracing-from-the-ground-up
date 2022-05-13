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

#include "MeshTriangle.h"

#include <algorithm>
#include <limits>

// the normal is computed in Grid::read_ply_file

MeshTriangle::MeshTriangle(Mesh* _mesh_ptr, const int i0, const int i1, const int i2) : GeometricObject(), mesh_ptr(_mesh_ptr), index0(i0), index1(i1), index2(i2) {}

MeshTriangle::~MeshTriangle() {
    if (mesh_ptr != nullptr) {
        delete mesh_ptr;
        mesh_ptr = nullptr;
    }
}

MeshTriangle::MeshTriangle(const MeshTriangle& mt) : GeometricObject(mt), index0(mt.index0), index1(mt.index1), index2(mt.index2), normal(mt.normal), area(mt.area) {
    // TODO: is it OK?
    mesh_ptr = new Mesh(*(mt.mesh_ptr));
}

MeshTriangle::MeshTriangle(MeshTriangle&& mt) noexcept
    : GeometricObject(std::move(mt)),
      index0(std::exchange(mt.index0, 0)),
      index1(std::exchange(mt.index1, 0)),
      index2(std::exchange(mt.index2, 0)),
      area(std::exchange(mt.area, 0.0f)),
      normal(std::move(mt.normal)) {
    mesh_ptr = mt.mesh_ptr;
    mt.mesh_ptr = nullptr;
}

MeshTriangle& MeshTriangle::operator=(const MeshTriangle& mt) {
    GeometricObject::operator=(mt);

    mesh_ptr = new Mesh(*(mt.mesh_ptr));  // TODO: is it OK?
    index0 = mt.index0;
    index1 = mt.index1;
    index2 = mt.index2;
    normal = mt.normal;

    return *this;
}

MeshTriangle& MeshTriangle::operator=(MeshTriangle&& mt) noexcept {
    GeometricObject::operator=(std::move(mt));

    index0 = std::exchange(mt.index0, 0);
    index1 = std::exchange(mt.index1, 0);
    index2 = std::exchange(mt.index2, 0);
    normal = std::move(mt.normal);
    area = std::exchange(mt.area, 0.0f);

    if (mesh_ptr != nullptr) {
        delete mesh_ptr;
    }
    mesh_ptr = mt.mesh_ptr;
    mt.mesh_ptr = nullptr;

    return *this;
}

void MeshTriangle::compute_normal(const bool reverse_normal) {
    normal = (mesh_ptr->vertices[index1] - mesh_ptr->vertices[index0]) ^ (mesh_ptr->vertices[index2] - mesh_ptr->vertices[index0]);
    normal.normalize();

    if (reverse_normal) {
        normal = -normal;
    }
}

// this is called in Grid::compute_mesh_normals

Normal MeshTriangle::get_normal() const { return normal; }

BBox MeshTriangle::get_bounding_box() {
    constexpr float delta = std::numeric_limits<float>::epsilon();  // to avoid degenerate bounding boxes

    Point3D v1(mesh_ptr->vertices[index0]);
    Point3D v2(mesh_ptr->vertices[index1]);
    Point3D v3(mesh_ptr->vertices[index2]);

    return BBox(std::min(std::min(v1.x, v2.x), v3.x) - delta, std::max(std::max(v1.x, v2.x), v3.x) + delta, std::min(std::min(v1.y, v2.y), v3.y) - delta, std::max(std::max(v1.y, v2.y), v3.y) + delta,
                std::min(std::min(v1.z, v2.z), v3.z) - delta, std::max(std::max(v1.z, v2.z), v3.z) + delta);
}

// this function is independent of the derived triangle type:
// flat, smooth, flat uv, smooth uv

bool MeshTriangle::shadow_hit(const Ray& ray, float& tmin) const {
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

    float r = r = e * l - h * i;
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

    return true;
}

// this is used for texture mapping in Chapter 29

float MeshTriangle::interpolate_u(const float beta, const float gamma) const { return (1.0f - beta - gamma) * mesh_ptr->u[index0] + beta * mesh_ptr->u[index1] + gamma * mesh_ptr->u[index2]; }

// this is used for texture mapping in Chapter 29

float MeshTriangle::interpolate_v(const float beta, const float gamma) const { return (1.0f - beta - gamma) * mesh_ptr->v[index0] + beta * mesh_ptr->v[index1] + gamma * mesh_ptr->v[index2]; }
