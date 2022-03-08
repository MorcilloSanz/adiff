#include "ImageTools.h"

#define STB_IMAGE_IMPLEMENTATION
#include "../vendor/stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "../vendor/stb_image_write.h"

ImageTools::Image ImageTools::loadPNG(const std::string& path) {
    std::vector<unsigned char> buffer;
    // Load image
    int width, height, bpp;
    unsigned char* buff = stbi_load(path.c_str(), &width, &height, &bpp, STBI_rgb_alpha);
    // Copy to buffer
    size_t bufferSize = width * height * 4;
    buffer.resize(bufferSize);
    memcpy(&buffer[0], buff, bufferSize);
    // Free first buffer
    stbi_image_free(buff);
    // Return image
    return Image(path, buffer, width, height, bpp);
}

void ImageTools::savePNG(const Image& image, const std::string& path) {
    stbi_write_png(path.c_str(), image.width, image.height, STBI_rgb_alpha, &image.buffer[0], image.width * STBI_rgb_alpha);
}