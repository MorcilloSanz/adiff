#include <stdio.h>
#include <stdlib.h>

#include "adiff_image.h"

#define STB_IMAGE_IMPLEMENTATION
#include <adiff/vendor/stb_image.h>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <adiff/vendor/stb_image_write.h>

ADIFF_IMAGE adiff_load_png(char* path) {

    ADIFF_IMAGE image;

    int width, height, bpp;
    unsigned char* buff = stbi_load(path, &width, &height, &bpp, STBI_rgb_alpha);

    image.width = width;
    image.height = height;
    image.bpp = bpp;
    image.buffer = buff;

    return image;
}

void adiff_save_png(ADIFF_IMAGE* image, char* path) {
    stbi_write_png(path, image->width, image->height, STBI_rgb_alpha, image->buffer, image->width * STBI_rgb_alpha);
}

void adiff_free_image(ADIFF_IMAGE* image) {
    stbi_image_free(image->buffer);
}