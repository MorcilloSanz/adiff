#include "filter.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void adiff_set_value(ADIFF_IMAGE* image, unsigned int x, unsigned int y, unsigned char value) {
    image->buffer[4 * (x + y * image->width)] = value;
    image->buffer[4 * (x + y * image->width) + 1] = value;
    image->buffer[4 * (x + y * image->width) + 2] = value;
}

unsigned char adiff_get_value(ADIFF_IMAGE* image, unsigned int x, unsigned int y) {
    return image->buffer[4 * (x + y * image->width)];
}

void adiff_grey_filter(ADIFF_IMAGE* image) {
    
    unsigned int size = image->width * image->height * 4;
    for(int i = 0; i < size; i += 4) {

        unsigned char r = image->buffer[i];
        unsigned char g = image->buffer[i + 1];
        unsigned char b = image->buffer[i + 2];

        unsigned char grey = 0.3 * r + 0.59 * g + 0.11 * b;
        image->buffer[i] = grey;
        image->buffer[i + 1] = grey;
        image->buffer[i + 2] = grey;
    }
}

void adiff_anisotropic_diffusion_filter(ADIFF_IMAGE* image, unsigned int iterations, float lambda, float k) {

    if(iterations == 0)
      return;

    for(int i = 0; i < image->width; i ++) {
        for(int j = 0; j < image->height; j ++) {
            if (i == 0 || i == image->width - 1 || j == 0 || j == image->height - 1) {
                adiff_set_value(image, i, j, adiff_get_value(image, i, j));
                continue;
            }

            double NI = adiff_get_value(image, i, j - 1) - adiff_get_value(image, i, j);
            double SI = adiff_get_value(image, i, j + 1) - adiff_get_value(image, i, j);
            double EI = adiff_get_value(image, i + 1, j) - adiff_get_value(image, i, j);
            double WI = adiff_get_value(image, i - 1, j) - adiff_get_value(image, i, j);

            double cN = exp( -pow(abs(NI) / k, 2) );
            double cS = exp( -pow(abs(SI) / k, 2) );
            double cE = exp( -pow(abs(EI) / k, 2) );
            double cW = exp( -pow(abs(WI) / k, 2) );

            double new_value = adiff_get_value(image, i, j) + lambda * (cN * NI + cS * SI + cE * EI + cW * WI);
            adiff_set_value(image, i, j, new_value);
        }
    }

    adiff_anisotropic_diffusion_filter(image, iterations - 1, lambda, k);
}