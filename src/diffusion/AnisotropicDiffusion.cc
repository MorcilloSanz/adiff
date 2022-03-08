#include "AnisotropicDiffusion.h"

#include <cmath>

AnisotropicDiffusion::AnisotropicDiffusion(const ImageTools::Image& _image, unsigned int _iterations, double _lambda, double _k)
    : image(_image), iterations(_iterations), lambda(_lambda), k(_k) {
    toGrey();
}

void AnisotropicDiffusion::setTemperature(unsigned int x, unsigned int y, unsigned char temperature) {
    // Ignore alpha channel
    image.buffer[4 * (x + y * image.width)] = temperature;
    image.buffer[4 * (x + y * image.width) + 1] = temperature;
    image.buffer[4 * (x + y * image.width) + 2] = temperature;
}

unsigned char AnisotropicDiffusion::getTemperature(unsigned int x, unsigned int y) {
    // Only take red channel (r = g = b)
    return image.buffer[4 * (x + y * image.width)];
}

void AnisotropicDiffusion::toGrey() {
    unsigned int index = 0;
    for(int i = 0; i < image.buffer.size(); i += 4) {
        unsigned char r = image.buffer[i];
        unsigned char g = image.buffer[i + 1];
        unsigned char b = image.buffer[i + 2];
        // Grey filter
        unsigned char grey = 0.3 * r + 0.59 * g + 0.11 * b;
        image.buffer[i] = grey;
        image.buffer[i + 1] = grey;
        image.buffer[i + 2] = grey;
    }
}

void AnisotropicDiffusion::applyDiffusion() {
    if(iterations == 0)
      return;

    // Diffusion algorithm
    for(int i = 0; i < image.width; i ++) {
        for(int j = 0; j < image.height; j ++) {
            if (i == 0 || i == image.width - 1 || j == 0 || j == image.height - 1) {
                setTemperature(i, j, getTemperature(i, j));
                continue;
            }

            double NI = getTemperature(i, j - 1) - getTemperature(i, j);
            double SI = getTemperature(i, j + 1) - getTemperature(i, j);
            double EI = getTemperature(i + 1, j) - getTemperature(i, j);
            double WI = getTemperature(i - 1, j) - getTemperature(i, j);

            double cN = exp( -pow(abs(NI) / k, 2) );
            double cS = exp( -pow(abs(SI) / k, 2) );
            double cE = exp( -pow(abs(EI) / k, 2) );
            double cW = exp( -pow(abs(WI) / k, 2) );

            double newTemperature = getTemperature(i, j) + lambda * (cN * NI + cS * SI + cE * EI + cW * WI);
            setTemperature(i, j, newTemperature);
        }
    }

    // Repeat 'iterations' times
    iterations--;
    applyDiffusion();
}