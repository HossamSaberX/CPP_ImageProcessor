#include "image.h"
#include "stb_image.h"


Image::Image(const std::string& filePath) {
    data = stbi_load(filePath.c_str(), &width, &height, &channels, 0);
}


Image::~Image() {
    stbi_image_free(data);
}

int Image::getWidth() const {
    return width;
}

int Image::getHeight() const {
    return height;
}

int Image::getChannels() const {
    return channels;
}

unsigned char* Image::getData() const {
    return data;
}