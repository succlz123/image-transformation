//
// Created by succlz123 on 17-8-7.
//

#include <iostream>
#include "../src/BurstLinker.h"

#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION

#include "../third_part/stb_image.h"
#include "../third_part/stb_image_write.h"

using namespace blk;

long long currentTimeMs() {
    std::chrono::time_point<std::chrono::system_clock, std::chrono::milliseconds> tp = std::chrono::time_point_cast<std::chrono::milliseconds>(
            std::chrono::system_clock::now());
    auto tmp = std::chrono::duration_cast<std::chrono::milliseconds>(tp.time_since_epoch());
    auto timestamp = tmp.count();
    return timestamp;
}

void addImage(const char *fileName, uint32_t width, uint32_t height, uint32_t delay, BurstLinker &burstLinker,
              QuantizerType quantizerType, DitherType ditherType) {
    uint32_t imageSize = width * height;
    if (imageSize < width || imageSize < height) {
        return;
    }
    int w, h, n;
    unsigned char *data = stbi_load(fileName, &w, &h, &n, 0);
    if (w != width || h != height) {
        std::cout << "Image is not the same width or height" << std::endl;
        return;
    }
    std::vector<uint32_t> image;
    image.reserve(imageSize);
    uint32_t index = 0;
    int a = 255;
    int r = 0;
    int g = 0;
    int b = 0;
    for (uint32_t i = 0; i < height; i++) {
        for (uint32_t j = 0; j < width; j++) {
            if (n == 3) {
                r = data[index++];
                g = data[index++];
                b = data[index++];
            } else if (n == 4) {
                r = data[index++];
                g = data[index++];
                b = data[index++];
                a = data[index++];
            } else {
                return;
            }
            image.push_back(a << 24 | b << 16 | g << 8 | r);
        }
    }
    stbi_image_free(data);
    int ignoreTranslucency = 0;
    int enableTransparency = (n == 4 ? 1 : 0);
    int transparencyOption = ignoreTranslucency << 8 | enableTransparency;

    std::vector<std::vector<uint32_t >> images;
    images.emplace_back(image);
    images.emplace_back(image);
}

void
addImage(int r, int g, int b, uint32_t width, uint32_t height, uint32_t delay, BurstLinker &burstLinker,
         QuantizerType quantizerType, DitherType ditherType) {
    uint32_t imageSize = width * height;
    if (imageSize < width || imageSize < height) {
        return;
    }
    std::vector<uint32_t> imagePixel;
    imagePixel.reserve(imageSize);
    for (uint32_t i = 0; i < width; i++) {
        for (uint32_t j = 0; j < height; j++) {
            imagePixel.push_back(b << 16 | g << 8 | r);
        }
    }
    int ignoreTranslucency = 1;
    int enableTransparency = 0;
    int transparencyOption = ignoreTranslucency << 8 | enableTransparency;
}

int main(int argc, char *argv[]) {
    const char *fileName = "../screenshot/timg.jpeg";
    int width, height, n;
    unsigned char *data = stbi_load(fileName, &width, &height, &n, 0);
    if (!data) {
        std::cout << "Image load failed" << std::endl;
        stbi_image_free(data);
        return 0;
    }
    if (width >= 65536 || height >= 65536) {
        std::cout << "Image is too large width = " << width << "height = " << height << std::endl;
        stbi_image_free(data);
        return 0;
    }

    long long currentTime = currentTimeMs();

    BurstLinker burstLinker;
    auto out = new unsigned char[width * height];
    burstLinker.grayScaleMaxMinAverage(data, out, width, height, n);
//    stbi_write_png("write.png", width, height, 1, out, width);

    long long diff = currentTimeMs() - currentTime;
    std::cout << "Uniform " << diff << "ms" << std::endl;

    currentTime = currentTimeMs();
    burstLinker.spotlightFilter(data, width, height, n);
    stbi_write_png("reverseColor.png", width, height, n, data, width * n);
    diff = currentTimeMs() - currentTime;
    std::cout << "reverseColor " << diff << "ms" << std::endl;

    stbi_image_free(data);
    return 0;
}
