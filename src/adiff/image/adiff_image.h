#pragma once

struct ADIFF_IMAGE {
    char* buffer;
    int width, height;
    int bpp;
};

typedef struct ADIFF_IMAGE ADIFF_IMAGE;

ADIFF_IMAGE adiff_load_png(char* path);
void adiff_save_png(ADIFF_IMAGE* image, char* path);

void adiff_free_image(ADIFF_IMAGE* image);