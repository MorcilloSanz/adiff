#pragma once

#include <iostream>
#include <vector>

class ImageTools {
public:
    struct Image {
        std::string path;
        std::vector<unsigned char> buffer;
        int width, height;
        int bpp;
        
        Image(const std::string& _path, const std::vector<unsigned char>& _buffer, int _width, int _height, int _bpp);
        Image(int _width, int _height, int _bpp);
        Image() = default;
        ~Image() = default;
    };
public:
    static Image loadPNG(const std::string& path);
    static void savePNG(const Image& image, const std::string& path);
};