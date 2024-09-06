#pragma once

#include <adiff/image/adiff_image.h>

/**
 * @brief Sets a pixel value in the coords (x,y) of the image
 * 
 * @param image the image
 * @param x the x coord
 * @param y the y coord
 * @param value the value of the pixel
 */
void adiff_set_value(ADIFF_IMAGE* image, unsigned int x, unsigned int y, unsigned char value);

/**
 * @brief Returns the value of a pixel in the coords (x,y) of the image
 * 
 * @param image the image
 * @param x the x coord
 * @param y the y coord
 * 
 * @return unsigned char 
 */
unsigned char adiff_get_value(ADIFF_IMAGE* image, unsigned int x, unsigned int y);

/**
 * @brief Applies a grey filter to the image
 * 
 * @param image the image
 */
void adiff_grey_filter(ADIFF_IMAGE* image);

/**
 * @brief Applies the anisotropic diffusion filter to the image
 * 
 * @pre the image MUST be in grey scale before applying this filter
 * 
 * @param image the image
 * @param iterations the number of iterations
 * @param lambda constant for controlling the amount of filtering (0 <= lambda <= 0.2)
 * @param k constant for controlling the sensitivity to edges, it is usually chosen experimentally or as a function of the noise in the image
 */
void adiff_anisotropic_diffusion_filter(ADIFF_IMAGE* image, unsigned int iterations, float lambda, float k);