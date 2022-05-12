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

#include "Compound.h"

#include <limits>

Compound::~Compound(void) { delete_objects(); }

Compound::Compound(const Compound& c) : GeometricObject(c) { copy_objects(c.objects); }

Compound::Compound(Compound&& c) noexcept : GeometricObject(std::move(c)), objects(std::move(c.objects)) {}

Compound& Compound::operator=(const Compound& c) {
    GeometricObject::operator=(c);

    copy_objects(c.objects);

    return (*this);
}

Compound& Compound::operator=(Compound&& c) noexcept {
    GeometricObject::operator=(std::move(c));

    objects = std::move(c.objects);

    return (*this);
}

Compound* Compound::clone(void) const { return (new Compound(*this)); }

void Compound::set_material(Material* material_ptr) {
    int num_objects = objects.size();

    for (int j = 0; j < num_objects; j++) objects[j]->set_material(material_ptr);
}

void Compound::add_object(GeometricObject* object_ptr) { objects.push_back(object_ptr); }

bool Compound::hit(const Ray& ray, float& tmin, ShadeRec& sr) const {
    float t;
    Normal normal;
    Point3D local_hit_point;
    bool hit = false;
    tmin = std::numeric_limits<float>::max();
    int num_objects = objects.size();

    for (int j = 0; j < num_objects; j++) {
        if (objects[j]->hit(ray, t, sr) && (t < tmin)) {
            hit = true;
            tmin = t;
            material_ptr = objects[j]->get_material();  // lhs is GeometricObject::material_ptr
            normal = sr.normal;
            local_hit_point = sr.local_hit_point;
        }
    }

    if (hit) {
        sr.t = tmin;
        sr.normal = normal;
        sr.local_hit_point = local_hit_point;
    }

    return (hit);
}

void Compound::delete_objects(void) {
    int num_objects = objects.size();

    for (int j = 0; j < num_objects; j++) {
        delete objects[j];
        objects[j] = nullptr;
    }

    objects.erase(objects.begin(), objects.end());
}

void Compound::copy_objects(const std::vector<GeometricObject*>& rhs_ojects) {
    delete_objects();
    int num_objects = rhs_ojects.size();

    for (int j = 0; j < num_objects; j++) {
        objects.push_back(rhs_ojects[j]->clone());
    }
}
