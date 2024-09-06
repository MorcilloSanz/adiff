#pragma once

#include <adiff/image/adiff_image.h>

void adiff_set_value(ADIFF_IMAGE* image, unsigned int x, unsigned int y, unsigned char value);
unsigned char adiff_get_value(ADIFF_IMAGE* image, unsigned int x, unsigned int y);

void adiff_grey_filter(ADIFF_IMAGE* image);
void adiff_anisotropic_diffusion_filter(ADIFF_IMAGE* image, unsigned int iterations, float lambda, float k);