#pragma once

#include "../image/ImageTools.h"

class EdgeDetector {
private:
    ImageTools::Image image, outputImage;
    double tau;
public:
    EdgeDetector(const ImageTools::Image& _image, double _tau);
    EdgeDetector() = default;
    ~EdgeDetector() = default;
private:
    void toGrey();
    void set(ImageTools::Image& image, unsigned char value, int x, int y);
    double get(ImageTools::Image& image, int x, int y);
public:
    void applyFilter();
public:
    inline ImageTools::Image& getImage() { return image; }
    inline ImageTools::Image& getOutputImage() { return outputImage; }
    inline double getTau() const { return tau; }
};