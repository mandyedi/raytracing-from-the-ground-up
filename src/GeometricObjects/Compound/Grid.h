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

#ifndef __GRID__
#define __GRID__

//     Copyright (C) Kevin Suffern 2000-2007.
//    This C++ code is for non-commercial purposes only.
//    This C++ code is licensed under the GNU General Public License Version 2.
//    See the file COPYING.txt for the full license.

// This contains the declaration of the class Grid.
// The copy constructor, assignment operator, and destructor, are dummy functions.
// The reason is that a grid can contain an arbitrary number of objects, can therefore be of arbitrary size.

// There is no set_bounding_box function because the bounding box is constructed in the setup_cells
// function.

// This Grid class is also way too large. All the triangle and PLY file code should be placed in
// a separate class called TriangleMesh that inherits from Grid.

#include <vector>

#include "Compound.h"

class ShadeRec;
class Mesh;

class Grid : public Compound {
public:

    Grid(void);

    Grid(Mesh* _mesh_ptr);

    ~Grid(void);

    // Yes, I was lazy at this point
    Grid(const Grid& grid) = delete;
    Grid(const Grid&& grid) = delete;
    Grid& operator=(const Grid& grid) = delete;
    Grid& operator=(Grid&& grid) = delete;

    void setup_cells(void);

    bool hit(const Ray& ray, float& tmin, ShadeRec& sr) const override;

    void read_flat_triangles(char* file_name);

    void read_smooth_triangles(char* file_name);

    void tessellate_flat_sphere(const int horizontal_steps, const int vertical_steps);

    void tessellate_smooth_sphere(const int horizontal_steps, const int vertical_steps);

    void reverse_mesh_normals(void);

    void store_material(Material* material, const int index);

private:

    std::vector<GeometricObject*> cells;
    int nx, ny, nz;  // number of cells in the x, y, and z directions
    BBox bbox;
    Mesh* mesh_ptr;
    bool reverse_normal;  // some PLY files have normals that point inwards

    Point3D find_min_bounds(void);

    Point3D find_max_bounds(void);

    void read_ply_file(char* file_name, const int triangle_type);

    void compute_mesh_normals(void);

    BBox get_bounding_box(void);

    void delete_cells(void);
};

inline void Grid::reverse_mesh_normals(void) { reverse_normal = true; }

// stores the material in the specified object
// this is called from the Rosette and Archway classes, which inherit from Grid
inline void Grid::store_material(Material* material_ptr, const int index) { objects[index]->set_material(material_ptr); }

#endif
