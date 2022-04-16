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


#include "Rectangle.h"
#include "../Samplers/Sampler.h"

const float Rectangle::kEpsilon = 0.001f;



Rectangle::Rectangle(const Point3D& _p0, const Vector3D& _a, const Vector3D& _b)
    :   GeometricObject(),
        p0(_p0),
        a(_a),
        b(_b),
        a_len_squared(a.len_squared()),
        b_len_squared(b.len_squared()),
        area(a.length() * b.length()),
        inv_area(1.0f / area),
        sampler_ptr(nullptr)
{
    normal = a ^ b;
    normal.normalize();
}




Rectangle::Rectangle(const Point3D& _p0, const Vector3D& _a, const Vector3D& _b, const Normal& n)
    :   GeometricObject(),
        p0(_p0),
        a(_a),
        b(_b),
        a_len_squared(a.len_squared()),
        b_len_squared(b.len_squared()),
        area(a.length() * b.length()),
        inv_area(1.0f / area),
        normal(n),
        sampler_ptr(nullptr)
{
    normal.normalize();
}



Rectangle::~Rectangle (void) {
    if (sampler_ptr != nullptr) {
        delete sampler_ptr;
        sampler_ptr = nullptr;
    }
}



Rectangle::Rectangle (const Rectangle& r)
    :   GeometricObject(r),
        p0(r.p0),
        a(r.a),
        b(r.b),
        a_len_squared(r.a_len_squared),
        b_len_squared(r.b_len_squared),
        normal(r.normal),
        area(r.area),
        inv_area(r.inv_area)
{
    sampler_ptr = r.sampler_ptr->clone();
}



Rectangle::Rectangle (Rectangle&& r) noexcept
    :   GeometricObject(std::move(r)),
        p0(std::move(r.p0)),
        a(std::move(r.a)),
        b(std::move(r.b)),
        a_len_squared(std::exchange(r.a_len_squared, 4.0f)),
        b_len_squared(std::exchange(r.b_len_squared, 4.0f)),
        normal(std::move(r.normal)),
        area(std::exchange(r.area, 4.0f)),
        inv_area(std::exchange(r.inv_area, 0.25f))
{
    sampler_ptr = r.sampler_ptr;
    r.sampler_ptr = nullptr;
}



Rectangle&
Rectangle::operator= (const Rectangle& r) {
    GeometricObject::operator=(r);

    p0              = r.p0;
    a               = r.a;
    b               = r.b;
    a_len_squared   = r.a_len_squared;
    b_len_squared   = r.b_len_squared;
    normal          = r.normal;
    area            = r.area;
    inv_area        = r.inv_area;

    if (sampler_ptr != nullptr) {
        delete sampler_ptr;
    }
    sampler_ptr = r.sampler_ptr->clone();

    return (*this);
}



Rectangle&
Rectangle::operator= (Rectangle&& r) noexcept {
    GeometricObject::operator=(std::move(r));

    p0              = std::move(r.p0);
    a               = std::move(r.a);
    b               = std::move(r.b);
    a_len_squared   = std::exchange(r.a_len_squared, 4.0f);
    b_len_squared   = std::exchange(r.b_len_squared, 4.0f);
    normal          = std::move(r.normal);
    area            = std::exchange(r.area, 4.0f);
    inv_area        = std::exchange(r.inv_area, 0.25f);

    if (sampler_ptr != nullptr) {
        delete sampler_ptr;
    }
    sampler_ptr = r.sampler_ptr;
    r.sampler_ptr = nullptr;

    return (*this);
}



Rectangle*
Rectangle::clone(void) const {
    return (new Rectangle(*this));
}



 BBox
 Rectangle::get_bounding_box() const {
    float delta = 0.0001;

    return(BBox(std::min(p0.x, p0.x + a.x + b.x) - delta, std::max(p0.x, p0.x + a.x + b.x) + delta,
                std::min(p0.y, p0.y + a.y + b.y) - delta, std::max(p0.y, p0.y + a.y + b.y) + delta,
                std::min(p0.z, p0.z + a.z + b.z) - delta, std::max(p0.z, p0.z + a.z + b.z) + delta));
 }




bool
Rectangle::hit(const Ray& ray, float& tmin, ShadeRec& sr) const {

    float t = (p0 - ray.o) * normal / (ray.d * normal);

    if (t <= kEpsilon)
        return (false);

    Point3D p = ray.o + t * ray.d;
    Vector3D d = p - p0;

    float ddota = d * a;

    if (ddota < 0.0f || ddota > a_len_squared)
        return (false);

    float ddotb = d * b;

    if (ddotb < 0.0f || ddotb > b_len_squared)
        return (false);

    tmin                = t;
    sr.normal           = normal;
    sr.local_hit_point  = p;

    return (true);
}




Point3D
Rectangle::sample(void) {
    Point2D sample_point = sampler_ptr->sample_unit_square();
    return (p0 + sample_point.x * a + sample_point.y * b);
}




Normal
Rectangle::get_normal(const Point3D& p) {
    return (normal);
}




float
Rectangle::pdf(const ShadeRec& sr) {
    return (inv_area);
}
