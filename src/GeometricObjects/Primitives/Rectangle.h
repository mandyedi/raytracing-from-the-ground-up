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

#ifndef __RECTANGLE__
#define __RECTANGLE__

#include "../GeometricObject.h"

class Sampler;

class Rectangle : public GeometricObject {
public:

    Rectangle() = default;

    explicit Rectangle(const Point3D& _p0, const Vector3D& _a, const Vector3D& _b);

    explicit Rectangle(const Point3D& _p0, const Vector3D& _a, const Vector3D& _b, const Normal& n);

    ~Rectangle();

    Rectangle(const Rectangle& r);

    Rectangle(Rectangle&& r) noexcept;

    Rectangle& operator=(const Rectangle& rhs);

    Rectangle& operator=(Rectangle&& rhs) noexcept;

    Rectangle* clone() const override;

    BBox get_bounding_box() const override;

    bool hit(const Ray& ray, float& t, ShadeRec& s) const override;

    // the following functions are used when the rectangle is a light source

    Point3D sample() override;

    Normal get_normal(const Point3D& p) override;

    float pdf(const ShadeRec& sr) override;

private:

    Point3D p0 = Point3D(-1.0f, 0.0f, -1.0f);  // corner vertex
    Vector3D a = Vector3D(0.0f, 0.0f, 2.0f);   // side
    Vector3D b = Vector3D(2.0f, 0.0f, 0.0f);   // side
    float a_len_squared = 4.0f;                // square of the length of side a
    float b_len_squared = 4.0f;                // square of the length of side b
    Normal normal = Normal(0.0f, 1.0f, 0.0f);

    float area = 4.0f;               // for rectangular lights
    float inv_area = 0.25f;          // for rectangular lights
    Sampler* sampler_ptr = nullptr;  // for rectangular lights

    static const float kEpsilon;
};

#endif
