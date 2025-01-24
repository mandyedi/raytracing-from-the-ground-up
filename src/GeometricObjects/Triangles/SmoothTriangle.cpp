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

#include "SmoothTriangle.h"

#include <algorithm>
#include <limits>
#include <utility>

SmoothTriangle::SmoothTriangle(const Point3D& a, const Point3D& b, const Point3D& c) : GeometricObject(), v0(a), v1(b), v2(c), n0(0.0f, 1.0f, 0.0f), n1(0.0f, 1.0f, 0.0f), n2(0.0f, 1.0f, 0.0f) {}

SmoothTriangle::SmoothTriangle(const SmoothTriangle& st) : GeometricObject(st), v0(st.v1), v1(st.v1), v2(st.v2), n0(st.n0), n1(st.n1), n2(st.n2) {}

SmoothTriangle::SmoothTriangle(SmoothTriangle&& st) noexcept
    : GeometricObject(std::move(st)), v0(std::move(st.v1)), v1(std::move(st.v1)), v2(std::move(st.v2)), n0(std::move(st.n0)), n1(std::move(st.n1)), n2(std::move(st.n2)) {}

SmoothTriangle& SmoothTriangle::operator=(const SmoothTriangle& st) {
    SmoothTriangle::operator=(st);
    v0 = st.v0;
    v1 = st.v1;
    v2 = st.v2;
    n0 = st.n0;
    n1 = st.n1;
    n2 = st.n2;

    return *this;
}

SmoothTriangle& SmoothTriangle::operator=(SmoothTriangle&& st) noexcept {
    SmoothTriangle::operator=(std::move(st));
    v0 = std::move(st.v0);
    v1 = std::move(st.v1);
    v2 = std::move(st.v2);
    n0 = std::move(st.n0);
    n1 = std::move(st.n1);
    n2 = std::move(st.n2);

    return *this;
}

SmoothTriangle* SmoothTriangle::clone() const { return new SmoothTriangle(*this); }

Normal SmoothTriangle::interpolate_normal(const float beta, const float gamma) const {
    Normal normal((1 - beta - gamma) * n0 + beta * n1 + gamma * n2);
    normal.normalize();

    return normal;
}

BBox SmoothTriangle::get_bounding_box() {
    constexpr float delta = std::numeric_limits<float>::epsilon();

    return BBox(std::min(std::min(v0.x, v1.x), v2.x) - delta, std::max(std::max(v0.x, v1.x), v2.x) + delta, std::min(std::min(v0.y, v1.y), v2.y) - delta, std::max(std::max(v0.y, v1.y), v2.y) + delta,
                std::min(std::min(v0.z, v1.z), v2.z) - delta, std::max(std::max(v0.z, v1.z), v2.z) + delta);
}

bool SmoothTriangle::hit(const Ray& ray, float& tmin, ShadeRec& sr) const {
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
    sr.normal = interpolate_normal(beta, gamma);
    sr.local_hit_point = ray.o + t * ray.d;

    return true;
}

bool SmoothTriangle::shadow_hit(const Ray& ray, float& tmin) const {
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

    return true;
}
