#pragma once

struct ADIFF_IMAGE {
    char* buffer;
    int width, height;
    int bpp;
};

typedef struct ADIFF_IMAGE ADIFF_IMAGE;

/**
 * @brief Loads a PNG image from a file
 * 
 * @param path the path of the file
 * @return ADIFF_IMAGE 
 */
ADIFF_IMAGE adiff_load_png(char* path);

/**
 * @brief Saves a PNG image to a file
 * 
 * @param image the image
 * @param path the file path
 */
void adiff_save_png(ADIFF_IMAGE* image, char* path);

/**
 * @brief Frees memory buffer of the image
 * 
 * @param image the image
 */
void adiff_free_image(ADIFF_IMAGE* image);