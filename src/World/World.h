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

#ifndef __WORLD__
#define __WORLD__


// The World class does not have a copy constructor or an assignment operator, for the followign reasons:

// 1    There's no need to copy construct or assign the World
// 2    We wouldn't want to do this anyway, because the world can contain an arbitray amount of data
// 3    These operations wouldn't work because the world is self-referencing:
//      the Tracer base class contains a pointer to the world. If we wrote a correct copy constructor for the
//      Tracer class, the World copy construtor would call itself recursively until we ran out of memory.


#include <vector>

#include "ViewPlane.h"
#include "../Utilities/RGBColor.h"
#include "../Utilities/ShadeRec.h"

class Tracer;
class Ray;
class GeometricObject;
class Camera;
class Light;

using namespace std;

class World {
    public:

        // tracer_ptr is set to NULL because the build functions will always construct the appropriate tracer
        // ambient_ptr is set to a default ambient light because this will do for most scenes
        // camera_ptr is set to NULL because the build functions will always have to construct a camera
        // and set its parameters
        // todo: Fix this, reference: C.41: A constructor should create a fully initialized object.

        ViewPlane                   vp = ViewPlane();
        RGBColor                    background_color = RGBColor::black; // TODO: Is world the best class to own this?
        Tracer*                     tracer_ptr = nullptr;
        Light*                      ambient_ptr = nullptr;
        Camera*                     camera_ptr = nullptr;
        vector<GeometricObject*>    objects;
        vector<Light*>              lights;

        World(void) = default;

        // For the sake of simplicity I prevent copy and move
        World(const World& w) = delete;
        World(World&& w) = delete;
        World& operator= (const World& rhs) = delete;
        World& operator= (World&& rhs) = delete;

        ~World();

        void
        add_object(GeometricObject* object_ptr);

        void
        add_light(Light* light_ptr);

        void
        set_ambient_light(Light* light_ptr);

        void
        set_camera(Camera* c_ptr);

        void
        build(void);

        // Chapter 3.6, Render single sphere
        // Chapter 3.9, Render multiple objects
        void
        render_scene(void) const;

        ShadeRec
        hit_objects(const Ray& ray);

        ShadeRec
        hit_bare_bones_objects(const Ray &ray);

        void
        display_pixel(const int row, const int column, const RGBColor& pixel_color) const;

        void
        save_to_ppm(void) const;

    private:

        mutable std::vector<int> pixels;

        void
        build_ch_03_page_one_image();

        void
        build_figure_03_18();

        void
        build_figure_03_20();

        RGBColor
        max_to_one(const RGBColor& c) const;

        RGBColor
        clamp_to_color(const RGBColor& c) const;

        void
        delete_objects(void);

        void
        delete_lights(void);
};



inline void
World::add_object(GeometricObject* object_ptr) {
    objects.push_back(object_ptr);
}



inline void
World::add_light(Light* light_ptr) {
    lights.push_back(light_ptr);
}



inline void
World::set_ambient_light(Light* light_ptr) {
    ambient_ptr = light_ptr;
}



inline void
World::set_camera(Camera* c_ptr) {
    camera_ptr = c_ptr;
}

#endif
