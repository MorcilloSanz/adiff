#pragma once

#include <iostream>

#include "../image/ImageTools.h"

class AnisotropicDiffusion {
private:
    ImageTools::Image image;
    unsigned int iterations;
    double lambda, k;
public:
    AnisotropicDiffusion(const ImageTools::Image& _image, unsigned int _iterations, double _lambda, double _k);
    AnisotropicDiffusion() = default;
    ~AnisotropicDiffusion() = default;
private:
    void setTemperature(unsigned int x, unsigned int y, unsigned char temperature);
    unsigned char getTemperature(unsigned int x, unsigned int y);
public:
    void toGrey();
    void applyDiffusion();
public:
    inline ImageTools::Image& getImage() {
        return image;
    }

    inline unsigned int getIterations() const {
        return iterations;
    }

    inline double getLambda() const {
        return lambda;
    }

    inline double getK() const {
        return k;
    }
};