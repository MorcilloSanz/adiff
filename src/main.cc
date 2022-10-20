#include <iostream>

#include "diffusion/AnisotropicDiffusion.h"
#include "edges/EdgeDetector.h"

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

    // Edges
    double tau = 0.08; // 0 <= tau <= 1
    EdgeDetector edgeDetector(image, tau);
    edgeDetector.applyFilter();

    // Save output
    ImageTools::savePNG(edgeDetector.getOutputImage(), "output-edges.png");

    return 0;
}