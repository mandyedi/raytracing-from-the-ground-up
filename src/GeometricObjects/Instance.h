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

#ifndef __INSTANCE__
#define __INSTANCE__

#include "../Utilities/Matrix.h"
#include "GeometricObject.h"

class Instance : public GeometricObject {
public:

    Instance() = default;

    Instance(GeometricObject* obj_ptr);

    virtual ~Instance();

    Instance(const Instance& instance);

    Instance(Instance&& instance) noexcept;

    Instance& operator=(const Instance& instance);

    Instance& operator=(Instance&& instance) noexcept;

    virtual Instance* clone() const;

    void set_object(GeometricObject* obj_ptr);

    void transform_texture(const bool transform);

    virtual void compute_bounding_box();

    virtual BBox get_bounding_box();

    virtual Material* get_material() const;

    virtual void set_material(Material* materialPtr);

    virtual bool hit(const Ray& ray, float& tmin, ShadeRec& sr) const;

    void translate(const Vector3D& trans);

    void translate(const float dx, const float dy, const float dz);

    void scale(const Vector3D& s);

    void scale(const float a, const float b, const float c);

    virtual void rotate_x(const float r);

    virtual void rotate_y(const float r);

    virtual void rotate_z(const float r);

    void shear(const Matrix& m);

private:
    GeometricObject* object_ptr = nullptr;  // object to be transformed
    Matrix inv_matrix;
    // TODO: static? check book
    static Matrix forward_matrix;  // transformation matrix
    BBox bbox;                     // transformed object's bounding box
    bool transform_the_texture = true;
};

inline void Instance::transform_texture(const bool transform) { transform_the_texture = transform; }

#endif
