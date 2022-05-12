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

#include "BeveledBox.h"

#include "../../Utilities/Normal.h"
#include "../../Utilities/Vector3D.h"
#include "../Instance.h"
#include "../Primitives/OpenCylinder.h"
#include "../Primitives/Rectangle.h"
#include "../Primitives/Sphere.h"

BeveledBox::BeveledBox(void) : Compound(), p0(-1.0f), p1(1.0f), rb(0.1f), bbox(p0, p1) {
    // edges
    // since the cylinders have to be defined initially in the vertical direction, it's easiest to use -(...)/2, +(...)/2 for
    // y0 and y1 in the constructors, and then rotate them about their centers.

    // top edges  (+ve y)

    Instance* top_front_edge = new Instance(new OpenCylinder(-(p1.x - p0.x - 2.0f * rb) * 0.5f, (p1.x - p0.x - 2.0f * rb) * 0.5f, rb));  // top front edge
    top_front_edge->rotate_z(90.0f);
    top_front_edge->translate((p0.x + p1.x) * 0.5f, p1.y - rb, p1.z - rb);
    top_front_edge->transform_texture(false);
    objects.push_back(top_front_edge);

    // top back (-ve z)

    Instance* top_back_edge = new Instance(new OpenCylinder(-(p1.x - p0.x - 2.0f * rb) * 0.5f, (p1.x - p0.x - 2.0f * rb) * 0.5f, rb));  // top back edge
    top_back_edge->rotate_z(90.0f);
    top_back_edge->translate((p0.x + p1.x) * 0.5f, p1.y - rb, p0.z + rb);
    top_back_edge->transform_texture(false);
    objects.push_back(top_back_edge);

    // top right (+ve x)

    Instance* top_right_edge = new Instance(new OpenCylinder(-(p1.z - p0.z - 2.0f * rb) * 0.5f, (p1.z - p0.z - 2.0f * rb) * 0.5f, rb));  // top right edge
    top_right_edge->rotate_x(90.0f);
    top_right_edge->translate(p1.x - rb, p1.y - rb, (p0.z + p1.z) * 0.5f);
    top_right_edge->transform_texture(false);
    objects.push_back(top_right_edge);

    // top left (-ve x)

    Instance* top_left_edge = new Instance(new OpenCylinder(-(p1.z - p0.z - 2.0f * rb) * 0.5f, (p1.z - p0.z - 2.0f * rb) * 0.5f, rb));  // top left edge
    top_left_edge->rotate_x(90.0f);
    top_left_edge->translate(p0.x + rb, p1.y - rb, (p0.z + p1.z) * 0.5f);
    top_left_edge->transform_texture(false);
    objects.push_back(top_left_edge);

    // bottom edges  (-ve y)

    // bottom front  (+ve z)

    Instance* bottom_front_edge = new Instance(new OpenCylinder(-(p1.x - p0.x - 2.0f * rb) * 0.5f, (p1.x - p0.x - 2.0f * rb) * 0.5f, rb));  // bottom fromt edge
    bottom_front_edge->rotate_z(90.0f);
    bottom_front_edge->translate((p0.x + p1.x) * 0.5f, p0.y + rb, p1.z - rb);
    bottom_front_edge->transform_texture(false);
    objects.push_back(bottom_front_edge);

    // bottom back  (-ve z)

    Instance* bottom_back_edge = new Instance(new OpenCylinder(-(p1.x - p0.x - 2.0f * rb) * 0.5f, (p1.x - p0.x - 2.0f * rb) * 0.5f, rb));  // bottom back edge
    bottom_back_edge->rotate_z(90.0f);
    bottom_back_edge->translate((p0.x + p1.x) * 0.5f, p0.y + rb, p0.z + rb);
    bottom_back_edge->transform_texture(false);
    objects.push_back(bottom_back_edge);

    // bottom right (-ve x, -ve y)

    Instance* bottom_right_edge = new Instance(new OpenCylinder(-(p1.z - p0.z - 2.0f * rb) * 0.5f, (p1.z - p0.z - 2.0f * rb) * 0.5f, rb));  // bottom right edge
    bottom_right_edge->rotate_x(90.0f);
    bottom_right_edge->translate(p1.x - rb, p0.y + rb, (p0.z + p1.z) * 0.5f);
    bottom_right_edge->transform_texture(false);
    objects.push_back(bottom_right_edge);

    // bottom left (-ve x, -ve y)

    Instance* bottom_left_edge = new Instance(new OpenCylinder(-(p1.z - p0.z - 2.0f * rb) * 0.5f, (p1.z - p0.z - 2.0f * rb) * 0.5f, rb));  // bottom left edge
    bottom_left_edge->rotate_x(90.0f);
    bottom_left_edge->translate(p0.x + rb, p0.y + rb, (p0.z + p1.z) * 0.5f);
    bottom_left_edge->transform_texture(false);
    objects.push_back(bottom_left_edge);

    // vertical edges

    // vertical right front  (+ve x, +ve z)

    Instance* vertical_right_front_edge = new Instance(new OpenCylinder(p0.y + rb, p1.y - rb, rb));
    vertical_right_front_edge->translate(p1.x - rb, 0.0f, p1.z - rb);
    vertical_right_front_edge->transform_texture(false);
    objects.push_back(vertical_right_front_edge);

    // vertical left front  (-ve x, +ve z)

    Instance* vertical_left_front_edge = new Instance(new OpenCylinder(p0.y + rb, p1.y - rb, rb));
    vertical_left_front_edge->translate(p0.x + rb, 0.0f, p1.z - rb);
    vertical_left_front_edge->transform_texture(false);
    objects.push_back(vertical_left_front_edge);

    // vertical left back  (-ve x, -ve z)

    Instance* vertical_left_back_edge = new Instance(new OpenCylinder(p0.y + rb, p1.y - rb, rb));
    vertical_left_back_edge->translate(p0.x + rb, 0.0f, p0.z + rb);
    vertical_left_back_edge->transform_texture(false);
    objects.push_back(vertical_left_back_edge);

    // vertical right back  (+ve x, -ve z)

    Instance* vertical_right_back_edge = new Instance(new OpenCylinder(p0.y + rb, p1.y - rb, rb));
    vertical_right_back_edge->translate(p1.x - rb, 0.0f, p0.z + rb);
    vertical_right_back_edge->transform_texture(false);
    objects.push_back(vertical_right_back_edge);

    // corner spheres

    // top right front

    Sphere* top_right_front_corner = new Sphere(Point3D(p1.x - rb, p1.y - rb, p1.z - rb), rb);
    objects.push_back(top_right_front_corner);

    // top left front  (-ve x)

    Sphere* top_left_front_corner = new Sphere(Point3D(p0.x + rb, p1.y - rb, p1.z - rb), rb);
    objects.push_back(top_left_front_corner);

    // top left back

    Sphere* top_left_back_corner = new Sphere(Point3D(p0.x + rb, p1.y - rb, p0.z + rb), rb);
    objects.push_back(top_left_back_corner);

    // top right back

    Sphere* top_right_back_corner = new Sphere(Point3D(p1.x - rb, p1.y - rb, p0.z + rb), rb);
    objects.push_back(top_right_back_corner);

    // bottom right front

    Sphere* bottom_right_front_corner = new Sphere(Point3D(p1.x - rb, p0.y + rb, p1.z - rb), rb);
    objects.push_back(bottom_right_front_corner);

    // bottom left front

    Sphere* bottom_left_front_corner = new Sphere(Point3D(p0.x + rb, p0.y + rb, p1.z - rb), rb);
    objects.push_back(bottom_left_front_corner);

    // bottom left back

    Sphere* bottom_left_back_corner = new Sphere(Point3D(p0.x + rb, p0.y + rb, p0.z + rb), rb);
    objects.push_back(bottom_left_back_corner);

    // bottom right back

    Sphere* bottom_right_back_corner = new Sphere(Point3D(p1.x - rb, p0.y + rb, p0.z + rb), rb);
    objects.push_back(bottom_right_back_corner);

    // the faces

    // bottom face: -ve y

    Rectangle* bottom_face =
        new Rectangle(Point3D(p0.x + rb, p0.y, p0.z + rb), Vector3D(0.0f, 0.0f, (p1.z - rb) - (p0.z + rb)), Vector3D((p1.x - rb) - (p0.x + rb), 0.0f, 0.0f), Normal(0.0f, -1.0f, 0.0f));
    objects.push_back(bottom_face);

    // bottom face: +ve y

    Rectangle* top_face =
        new Rectangle(Point3D(p0.x + rb, p1.y, p0.z + rb), Vector3D(0.0f, 0.0f, (p1.z - rb) - (p0.z + rb)), Vector3D((p1.x - rb) - (p0.x + rb), 0.0f, 0.0f), Normal(0.0f, 1.0f, 0.0f));
    objects.push_back(top_face);

    // back face: -ve z

    Rectangle* back_face = new Rectangle(Point3D(p0.x + rb, p0.y + rb, p0.z), Vector3D((p1.x - rb) - (p0.x + rb), 0.0f, 0.0f), Vector3D(0.0f, (p1.y - rb) - (p0.y + rb), 0.0f), Normal(0.0f, 0.0f, -1));
    objects.push_back(back_face);

    // front face: +ve z

    Rectangle* front_face =
        new Rectangle(Point3D(p0.x + rb, p0.y + rb, p1.z), Vector3D((p1.x - rb) - (p0.x + rb), 0.0f, 0.0f), Vector3D(0.0f, (p1.y - rb) - (p0.y + rb), 0.0f), Normal(0.0f, 0.0f, 1.0f));
    objects.push_back(front_face);

    // left face: -ve x

    Rectangle* left_face =
        new Rectangle(Point3D(p0.x, p0.y + rb, p0.z + rb), Vector3D(0.0f, 0.0f, (p1.z - rb) - (p0.z + rb)), Vector3D(0.0f, (p1.y - rb) - (p0.y + rb), 0.0f), Normal(-1.0f, 0.0f, 0.0f));
    objects.push_back(left_face);

    // right face: +ve x

    Rectangle* right_face =
        new Rectangle(Point3D(p1.x, p0.y + rb, p0.z + rb), Vector3D(0.0f, 0.0f, (p1.z - rb) - (p0.z + rb)), Vector3D(0.0f, (p1.y - rb) - (p0.y + rb), 0.0f), Normal(1.0f, 0.0f, 0.0f));
    objects.push_back(right_face);
}

BeveledBox::BeveledBox(const Point3D& min_corner, const Point3D& max_corner, const float bevel_radius) : Compound(), p0(min_corner), p1(max_corner), rb(bevel_radius), bbox(p0, p1) {
    // edges
    // since the cylinders have to be defined initially in the vertical direction, it's easiest to use -(...)/2, +(...)/2 for
    // y0 and y1 in the constructors, and then rotate them about their centers.

    // top edges  (+ve y)

    Instance* top_front_edge = new Instance(new OpenCylinder(-(p1.x - p0.x - 2.0f * rb) * 0.5f, (p1.x - p0.x - 2.0f * rb) * 0.5f, rb));  // top front edge
    top_front_edge->rotate_z(90.0f);
    top_front_edge->translate((p0.x + p1.x) * 0.5f, p1.y - rb, p1.z - rb);
    top_front_edge->transform_texture(false);
    objects.push_back(top_front_edge);

    // top back (-ve z)

    Instance* top_back_edge = new Instance(new OpenCylinder(-(p1.x - p0.x - 2.0f * rb) * 0.5f, (p1.x - p0.x - 2.0f * rb) * 0.5f, rb));  // top back edge
    top_back_edge->rotate_z(90.0f);
    top_back_edge->translate((p0.x + p1.x) * 0.5f, p1.y - rb, p0.z + rb);
    top_back_edge->transform_texture(false);
    objects.push_back(top_back_edge);

    // top right (+ve x)

    Instance* top_right_edge = new Instance(new OpenCylinder(-(p1.z - p0.z - 2.0f * rb) * 0.5f, (p1.z - p0.z - 2.0f * rb) * 0.5f, rb));  // top right edge
    top_right_edge->rotate_x(90.0f);
    top_right_edge->translate(p1.x - rb, p1.y - rb, (p0.z + p1.z) * 0.5f);
    top_right_edge->transform_texture(false);
    objects.push_back(top_right_edge);

    // top left (-ve x)

    Instance* top_left_edge = new Instance(new OpenCylinder(-(p1.z - p0.z - 2.0f * rb) * 0.5f, (p1.z - p0.z - 2.0f * rb) * 0.5f, rb));  // top left edge
    top_left_edge->rotate_x(90.0f);
    top_left_edge->translate(p0.x + rb, p1.y - rb, (p0.z + p1.z) * 0.5f);
    top_left_edge->transform_texture(false);
    objects.push_back(top_left_edge);

    // bottom edges  (-ve y)

    // bottom front  (+ve z)

    Instance* bottom_front_edge = new Instance(new OpenCylinder(-(p1.x - p0.x - 2.0f * rb) * 0.5f, (p1.x - p0.x - 2.0f * rb) * 0.5f, rb));  // bottom fromt edge
    bottom_front_edge->rotate_z(90.0f);
    bottom_front_edge->translate((p0.x + p1.x) * 0.5f, p0.y + rb, p1.z - rb);
    bottom_front_edge->transform_texture(false);
    objects.push_back(bottom_front_edge);

    // bottom back  (-ve z)

    Instance* bottom_back_edge = new Instance(new OpenCylinder(-(p1.x - p0.x - 2.0f * rb) * 0.5f, (p1.x - p0.x - 2.0f * rb) * 0.5f, rb));  // bottom back edge
    bottom_back_edge->rotate_z(90.0f);
    bottom_back_edge->translate((p0.x + p1.x) * 0.5f, p0.y + rb, p0.z + rb);
    bottom_back_edge->transform_texture(false);
    objects.push_back(bottom_back_edge);

    // bottom right (-ve x, -ve y)

    Instance* bottom_right_edge = new Instance(new OpenCylinder(-(p1.z - p0.z - 2.0f * rb) * 0.5f, (p1.z - p0.z - 2.0f * rb) * 0.5f, rb));  // bottom right edge
    bottom_right_edge->rotate_x(90.0f);
    bottom_right_edge->translate(p1.x - rb, p0.y + rb, (p0.z + p1.z) * 0.5f);
    bottom_right_edge->transform_texture(false);
    objects.push_back(bottom_right_edge);

    // bottom left (-ve x, -ve y)

    Instance* bottom_left_edge = new Instance(new OpenCylinder(-(p1.z - p0.z - 2.0f * rb) * 0.5f, (p1.z - p0.z - 2.0f * rb) * 0.5f, rb));  // bottom left edge
    bottom_left_edge->rotate_x(90.0f);
    bottom_left_edge->translate(p0.x + rb, p0.y + rb, (p0.z + p1.z) * 0.5f);
    bottom_left_edge->transform_texture(false);
    objects.push_back(bottom_left_edge);

    // vertical edges

    // vertical right front  (+ve x, +ve z)

    Instance* vertical_right_front_edge = new Instance(new OpenCylinder(p0.y + rb, p1.y - rb, rb));
    vertical_right_front_edge->translate(p1.x - rb, 0.0f, p1.z - rb);
    vertical_right_front_edge->transform_texture(false);
    objects.push_back(vertical_right_front_edge);

    // vertical left front  (-ve x, +ve z)

    Instance* vertical_left_front_edge = new Instance(new OpenCylinder(p0.y + rb, p1.y - rb, rb));
    vertical_left_front_edge->translate(p0.x + rb, 0.0f, p1.z - rb);
    vertical_left_front_edge->transform_texture(false);
    objects.push_back(vertical_left_front_edge);

    // vertical left back  (-ve x, -ve z)

    Instance* vertical_left_back_edge = new Instance(new OpenCylinder(p0.y + rb, p1.y - rb, rb));
    vertical_left_back_edge->translate(p0.x + rb, 0.0f, p0.z + rb);
    vertical_left_back_edge->transform_texture(false);
    objects.push_back(vertical_left_back_edge);

    // vertical right back  (+ve x, -ve z)

    Instance* vertical_right_back_edge = new Instance(new OpenCylinder(p0.y + rb, p1.y - rb, rb));
    vertical_right_back_edge->translate(p1.x - rb, 0.0f, p0.z + rb);
    vertical_right_back_edge->transform_texture(false);
    objects.push_back(vertical_right_back_edge);

    // corner spheres

    // top right front

    Sphere* top_right_front_corner = new Sphere(Point3D(p1.x - rb, p1.y - rb, p1.z - rb), rb);
    objects.push_back(top_right_front_corner);

    // top left front  (-ve x)

    Sphere* top_left_front_corner = new Sphere(Point3D(p0.x + rb, p1.y - rb, p1.z - rb), rb);
    objects.push_back(top_left_front_corner);

    // top left back

    Sphere* top_left_back_corner = new Sphere(Point3D(p0.x + rb, p1.y - rb, p0.z + rb), rb);
    objects.push_back(top_left_back_corner);

    // top right back

    Sphere* top_right_back_corner = new Sphere(Point3D(p1.x - rb, p1.y - rb, p0.z + rb), rb);
    objects.push_back(top_right_back_corner);

    // bottom right front

    Sphere* bottom_right_front_corner = new Sphere(Point3D(p1.x - rb, p0.y + rb, p1.z - rb), rb);
    objects.push_back(bottom_right_front_corner);

    // bottom left front

    Sphere* bottom_left_front_corner = new Sphere(Point3D(p0.x + rb, p0.y + rb, p1.z - rb), rb);
    objects.push_back(bottom_left_front_corner);

    // bottom left back

    Sphere* bottom_left_back_corner = new Sphere(Point3D(p0.x + rb, p0.y + rb, p0.z + rb), rb);
    objects.push_back(bottom_left_back_corner);

    // bottom right back

    Sphere* bottom_right_back_corner = new Sphere(Point3D(p1.x - rb, p0.y + rb, p0.z + rb), rb);
    objects.push_back(bottom_right_back_corner);

    // the faces

    // bottom face: -ve y

    Rectangle* bottom_face =
        new Rectangle(Point3D(p0.x + rb, p0.y, p0.z + rb), Vector3D(0.0f, 0.0f, (p1.z - rb) - (p0.z + rb)), Vector3D((p1.x - rb) - (p0.x + rb), 0.0f, 0.0f), Normal(0.0f, -1.0f, 0.0f));
    objects.push_back(bottom_face);

    // bottom face: +ve y

    Rectangle* top_face =
        new Rectangle(Point3D(p0.x + rb, p1.y, p0.z + rb), Vector3D(0.0f, 0.0f, (p1.z - rb) - (p0.z + rb)), Vector3D((p1.x - rb) - (p0.x + rb), 0.0f, 0.0f), Normal(0.0f, 1.0f, 0.0f));
    objects.push_back(top_face);

    // back face: -ve z

    Rectangle* back_face = new Rectangle(Point3D(p0.x + rb, p0.y + rb, p0.z), Vector3D((p1.x - rb) - (p0.x + rb), 0.0f, 0.0f), Vector3D(0.0f, (p1.y - rb) - (p0.y + rb), 0.0f), Normal(0.0f, 0.0f, -1));
    objects.push_back(back_face);

    // front face: +ve z

    Rectangle* front_face =
        new Rectangle(Point3D(p0.x + rb, p0.y + rb, p1.z), Vector3D((p1.x - rb) - (p0.x + rb), 0.0f, 0.0f), Vector3D(0.0f, (p1.y - rb) - (p0.y + rb), 0.0f), Normal(0.0f, 0.0f, 1.0f));
    objects.push_back(front_face);

    // left face: -ve x

    Rectangle* left_face =
        new Rectangle(Point3D(p0.x, p0.y + rb, p0.z + rb), Vector3D(0.0f, 0.0f, (p1.z - rb) - (p0.z + rb)), Vector3D(0.0f, (p1.y - rb) - (p0.y + rb), 0.0f), Normal(-1.0f, 0.0f, 0.0f));
    objects.push_back(left_face);

    // right face: +ve x

    Rectangle* right_face =
        new Rectangle(Point3D(p1.x, p0.y + rb, p0.z + rb), Vector3D(0.0f, 0.0f, (p1.z - rb) - (p0.z + rb)), Vector3D(0.0f, (p1.y - rb) - (p0.y + rb), 0.0f), Normal(1.0f, 0.0f, 0.0f));
    objects.push_back(right_face);
}

BeveledBox::~BeveledBox(void) {}

BeveledBox::BeveledBox(const BeveledBox& bb) : Compound(bb), p0(bb.p0), p1(bb.p1), rb(bb.rb), bbox(bb.bbox) {}

BeveledBox::BeveledBox(BeveledBox&& bb) noexcept : Compound(std::move(bb)), p0(std::move(bb.p0)), p1(std::move(bb.p1)), rb(std::exchange(bb.rb, 0.1f)), bbox(std::move(bb.bbox)) {}

BeveledBox& BeveledBox::operator=(const BeveledBox& bb) {
    Compound::operator=(bb);

    p0 = bb.p0;
    p1 = bb.p1;
    rb = bb.rb;
    bbox = bb.bbox;

    return (*this);
}

BeveledBox& BeveledBox::operator=(BeveledBox&& bb) noexcept {
    Compound::operator=(std::move(bb));

    p0 = std::move(bb.p0);
    p1 = std::move(bb.p1);
    rb = std::exchange(bb.rb, 0.1f);
    bbox = std::move(bb.bbox);

    return (*this);
}

BeveledBox* BeveledBox::clone(void) const { return (new BeveledBox(*this)); }

bool BeveledBox::shadow_hit(const Ray& ray, float& tmin) const {
    if (bbox.hit(ray)) {
        return (Compound::shadow_hit(ray, tmin));
    } else {
        return (false);
    }
}

bool BeveledBox::hit(const Ray& ray, float& tmin, ShadeRec& sr) const {
    if (bbox.hit(ray)) {
        return (Compound::hit(ray, tmin, sr));
    } else {
        return (false);
    }
}
