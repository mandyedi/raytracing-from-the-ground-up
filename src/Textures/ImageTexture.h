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

#ifndef __IMAGE_TEXTURE__
#define __IMAGE_TEXTURE__

#include "Texture.h"
#include "../Utilities/Image.h"
#include "../Mappings/Mapping.h"


class ImageTexture: public Texture {
    public:
 
        ImageTexture() = default;

        ImageTexture(Image* _image_ptr);

        virtual ~ImageTexture();

        ImageTexture(const ImageTexture& it);

        ImageTexture& operator= (const ImageTexture& rhs);

        virtual ImageTexture* clone() const;

        virtual RGBColor get_color(const ShadeRec& sr) const;

        void set_image(Image* _image_ptr);

        void set_mapping(Mapping* map_ptr);

    private:

        int hres = 100;
        int vres = 100;
        Image* image_ptr = nullptr;
        Mapping* mapping_ptr = nullptr;
};

inline void ImageTexture::set_image(Image* _image_ptr) {
    image_ptr = _image_ptr;
    hres = image_ptr->get_hres();
    vres = image_ptr->get_vres();
}

inline void ImageTexture::set_mapping(Mapping* map_ptr) {
    mapping_ptr = map_ptr;
}

#endif
