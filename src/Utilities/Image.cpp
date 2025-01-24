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

#include <iostream>
#include <cstdio>

#include "Image.h"
#include "RGBColor.h"

void Image::read_ppm_file(const char *file_name) {
    FILE *file = fopen(file_name, "rb");

    if (file == 0) {
        std::cout << "could not open file" << std::endl;
        return;
    }
    else {
        std::cout << "file opened" << std::endl;
    }

    unsigned char ppm_type;
    if (fscanf(file, "P%c\n", &ppm_type) != 1) {
        std::cout << "Invalid PPM signature" << std::endl;
    }

    if (ppm_type != '6') {
        std::cout << "Only binary PPM supported" << std::endl;
    }

    unsigned char dummy;
    while (fscanf(file, "#%c", &dummy))
        while (fgetc(file) != '\n');

    if (fscanf(file, "%d %d\n", &hres, &vres) != 2) {
        std::cout << "Invalid image size" << std::endl;
    }

    if (hres <= 0) {
        std::cout << "Invalid image width" << std::endl;
    }
    else {
        std::cout << "hres = " << hres << std::endl;
    }

    if (vres <= 0) {
        std::cout << "Invalid image height" << std::endl;
    }
    else {
        std::cout << "vres = " << vres << std::endl;
    }

    unsigned int max_value = 0;
    if (fscanf(file, "%d\n", &max_value) != 1) {
        std::cout << "Invalid max value" << std::endl;
    }

    float inv_max_value = 1.0 / (float)max_value;

    pixels.reserve(hres * vres);

    for (unsigned int y = 0; y < vres; y++) {
        for (unsigned int x = 0; x < hres; x++) {
            unsigned char red;
            unsigned char green;
            unsigned char blue;

            if (fscanf(file, "%c%c%c", &red, &green, &blue) != 3) {
                std::cout << "Invalid image" << std::endl;
            }

            float r = red * inv_max_value;
            float g = green * inv_max_value;
            float b = blue * inv_max_value;

            pixels.push_back(RGBColor(r, g, b));
        }
    }

    fclose(file);

    std::cout << "finished reading PPM file" << std::endl;
}

RGBColor Image::get_color(const int row, const int column) const {
    int index = column + hres * (vres - row - 1);
    int pixels_size = pixels.size();

    if (index < pixels_size) {
        return (pixels[index]);
    }
    else {
        return RGBColor::red;
    }
}


