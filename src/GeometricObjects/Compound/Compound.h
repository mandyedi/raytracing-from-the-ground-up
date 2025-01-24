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

#ifndef __COMPOUND__
#define __COMPOUND__

#include <vector>

#include "../GeometricObject.h"

class Compound : public GeometricObject {
public:

    Compound() = default;

    virtual ~Compound();

    Compound(const Compound& c);

    Compound(Compound&& c) noexcept;

    Compound& operator=(const Compound& c);

    Compound& operator=(Compound&& c) noexcept;

    Compound* clone() const override;

    void set_material(Material* material_ptr);

    void add_object(GeometricObject* object_ptr) override;

    int get_num_objects();

    virtual bool hit(const Ray& ray, float& tmin, ShadeRec& s) const override;

protected:

    std::vector<GeometricObject*> objects;

private:

    void delete_objects();

    void copy_objects(const std::vector<GeometricObject*>& rhs_objects);
};

inline int Compound::get_num_objects() { return objects.size(); }

#endif
