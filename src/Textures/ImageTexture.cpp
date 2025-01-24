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

#include "ImageTexture.h"

ImageTexture::ImageTexture(Image* _image_ptr)
    :    Texture(),
        hres(_image_ptr->get_hres()),
        vres(_image_ptr->get_vres()),
        image_ptr(_image_ptr),
        mapping_ptr(nullptr)
{}

ImageTexture::~ImageTexture() {

    if (image_ptr) {
        delete image_ptr;
        image_ptr = nullptr;
    }

    if (mapping_ptr) {
        delete mapping_ptr;
        mapping_ptr = nullptr;
    }
}

ImageTexture::ImageTexture(const ImageTexture& it)
    :     Texture(it),
        hres(it.hres),
        vres(it.vres)
{
    if (it.image_ptr) {
        *image_ptr = *it.image_ptr;
    }
    else {
        image_ptr = nullptr;
    }
        
    if (it.mapping_ptr) {
        mapping_ptr = it.mapping_ptr->clone();
    }
    else {
        mapping_ptr = nullptr;
    }
}

ImageTexture& ImageTexture::operator= (const ImageTexture& rhs) {
    Texture::operator=(rhs);
    hres = rhs.hres;
    vres = rhs.vres;
    
    if (image_ptr) {
        delete image_ptr;
        image_ptr = nullptr;
    }
    *image_ptr = *rhs.image_ptr;
    
    if (mapping_ptr) {
        delete mapping_ptr;
        mapping_ptr = nullptr;
    }
    
    if (rhs.mapping_ptr) {
        mapping_ptr = rhs.mapping_ptr->clone();
    }

    return *this;
}

ImageTexture *ImageTexture::clone() const {
    return new ImageTexture(*this);
}

// When we ray trace a triangle mesh object with uv mapping, the mapping pointer may be NULL
// because we can define uv coordinates on an arbitrary triangle mesh.
// In this case we don't use the local hit point because the pixel coordinates are computed 
// from the uv coordinates stored in the ShadeRec object in the uv triangles' hit functions
// See, for example, Listing 29.12.

RGBColor ImageTexture::get_color(const ShadeRec& sr) const {
    int row;
    int column;
        
    if (mapping_ptr) {
        mapping_ptr->get_texel_coordinates(sr.local_hit_point, hres, vres, row, column);
    }
    else {
        row = static_cast<int>(sr.v * (vres - 1)); 
        column = static_cast<int>(sr.u * (hres - 1));
    }
    
    return image_ptr->get_color(row, column);
}  





