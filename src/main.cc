#include <iostream>

#include "diffusion/AnisotropicDiffusion.h"

int main() {

    // Input
    unsigned int iterations = 50;
    double lambda = 0.20;
    double k = 10;
    ImageTools::Image image = ImageTools::loadPNG("albert-einstein.png");
    
    // Diffusion
    AnisotropicDiffusion anisotropicDiffusion(image, iterations, lambda, k);
    anisotropicDiffusion.applyDiffusion();

    // Save output
    ImageTools::savePNG(anisotropicDiffusion.getImage(), "output.png");

    return 0;
}