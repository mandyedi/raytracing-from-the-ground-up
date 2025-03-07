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

#include "World.h"

#include <ctime>
#include <fstream>
#include <iomanip>
#include <limits>
#include <sstream>

#include "../Cameras/Camera.h"
#include "../GeometricObjects/GeometricObject.h"
#include "../Lights/Light.h"
#include "../Tracers/Tracer.h"

World::~World() {
    if (tracer_ptr) {
        delete tracer_ptr;
        tracer_ptr = nullptr;
    }

    if (ambient_ptr) {
        delete ambient_ptr;
        ambient_ptr = nullptr;
    }

    if (camera_ptr) {
        delete camera_ptr;
        camera_ptr = nullptr;
    }

    delete_objects();
    delete_lights();
}

void World::build() {
    // build_ch_03_page_one_image();
    // build_figure_03_18();
    // build_figure_03_20();
    build_figure_04_04();
}

void World::render_scene() const {
    RGBColor pixel_color;
    Ray ray;
    int hres = vp.hres;
    int vres = vp.vres;
    float s = vp.s;
    float zw = 100.0f;
    float x = 0.0f;
    float y = 0.0f;

    ray.d = Vector3D(0.0f, 0.0f, -1.0f);

    for (int r = 0; r < vres; r++) {      // up
        for (int c = 0; c < hres; c++) {  // across
            x = vp.s * (static_cast<float>(c) - 0.5f * (static_cast<float>(vp.hres) - 1.0f));
            y = vp.s * (static_cast<float>(r) - 0.5f * (static_cast<float>(vp.vres) - 1.0f));
            ray.o = Point3D(x, y, zw);
            pixel_color = tracer_ptr->trace_ray(ray);
            display_pixel(r, c, pixel_color);
        }
    }

    save_to_ppm();
}

ShadeRec World::hit_objects(const Ray& ray) {
    ShadeRec sr(*this);
    float t;
    Normal normal;
    Point3D local_hit_point;
    float tmin = std::numeric_limits<float>::max();
    size_t num_objects = objects.size();

    for (size_t j = 0; j < num_objects; j++) {
        if (objects[j]->hit(ray, t, sr) && (t < tmin)) {
            sr.hit_an_object = true;
            tmin = t;
            sr.material_ptr = objects[j]->get_material();
            sr.hit_point = ray.o + t * ray.d;
            normal = sr.normal;
            local_hit_point = sr.local_hit_point;
        }
    }

    if (sr.hit_an_object) {
        sr.t = tmin;
        sr.normal = normal;
        sr.local_hit_point = local_hit_point;
    }

    return sr;
}

ShadeRec World::hit_bare_bones_objects(const Ray& ray) {
    ShadeRec sr(*this);
    float t;
    float tmin = std::numeric_limits<float>::max();
    size_t num_objects = objects.size();

    for (size_t j = 0; j < num_objects; j++) {
        if (objects[j]->hit(ray, t, sr) && (t < tmin)) {
            sr.hit_an_object = true;
            tmin = t;
            sr.color = objects[j]->get_color();
        }
    }

    return sr;
}

// raw_color is the pixel color computed by the ray tracer
// its RGB floating point components can be arbitrarily large
// mapped_color has all components in the range [0, 1], but still floating point
// display color has integer components for computer display
// the Mac's components are in the range [0, 65535]
// a PC's components will probably be in the range [0, 255]
// the system-dependent code is in the function convert_to_display_color
// the function SetCPixel is a Mac OS function

void World::display_pixel([[maybe_unused]] const int row, [[maybe_unused]] const int column, const RGBColor& raw_color) const {
    RGBColor mapped_color;

    if (vp.show_out_of_gamut) {
        mapped_color = clamp_to_color(raw_color);
    } else {
        mapped_color = max_to_one(raw_color);
    }

    if (vp.gamma != 1.0f) {
        mapped_color = mapped_color.powc(vp.inv_gamma);
    }

    pixels.push_back((int)(mapped_color.r * 255));
    pixels.push_back((int)(mapped_color.g * 255));
    pixels.push_back((int)(mapped_color.b * 255));
}

void World::save_to_ppm() const {
    std::time_t t = std::time(nullptr);
    std::tm tm = *std::localtime(&t);
    std::stringstream imageFile;
    imageFile << "./image_" << std::put_time(&tm, "%Y%m%e%H%M%S") << ".ppm";

    std::ofstream ofs;
    ofs.open(imageFile.str().c_str(), std::ios::out | std::ios::binary);
    ofs << "P6\n" << vp.hres << " " << vp.vres << "\n255\n";

    // The view plane's origin is on the bottom left
    // PPM image format goes from top to bottom
    int numberOfPixels = pixels.size();
    for (int rowIndex = 1; rowIndex <= vp.vres; rowIndex++) {
        for (int columnIndex = 0; columnIndex < vp.hres * 3; columnIndex++) {
            int pixel = pixels[numberOfPixels - (vp.hres * 3 * rowIndex) + columnIndex];
            ofs << static_cast<unsigned char>(pixel);
        }
    }

    // for (int i : pixels) {
    //     ofs << static_cast<unsigned char>(i);
    // }

    ofs.close();
}

RGBColor World::max_to_one(const RGBColor& c) const {
    float max_value = max(c.r, max(c.g, c.b));

    if (max_value > 1.0f) {
        return c / max_value;
    } else {
        return c;
    }
}

// Set color to red if any component is greater than one

RGBColor World::clamp_to_color(const RGBColor& raw_color) const {
    RGBColor c(raw_color);

    if (raw_color.r > 1.0f || raw_color.g > 1.0f || raw_color.b > 1.0f) {
        c.r = 1.0f;
        c.g = 0.0f;
        c.b = 0.0f;
    }

    return c;
}

// Deletes the objects in the objects array, and erases the array.
// The objects array still exists, because it's an automatic variable, but it's empty

void World::delete_objects() {
    size_t num_objects = objects.size();

    for (size_t j = 0; j < num_objects; j++) {
        delete objects[j];
        objects[j] = nullptr;
    }

    objects.erase(objects.begin(), objects.end());
}

void World::delete_lights() {
    size_t num_lights = lights.size();

    for (size_t j = 0; j < num_lights; j++) {
        delete lights[j];
        lights[j] = nullptr;
    }

    lights.erase(lights.begin(), lights.end());
}
