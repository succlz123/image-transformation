//
// Created by succlz123 on 2018/1/30.
//

#include <cmath>
#include "BurstLinker.h"
#include "GifAnalyzer.h"

using namespace blk;

//Gray = (R*1 + G*2 + B*1) >> 2
//Gray = (R*2 + G*5 + B*1) >> 3
//Gray = (R*4 + G*10 + B*2) >> 4
//Gray = (R*9 + G*19 + B*4) >> 5
//Gray = (R*19 + G*37 + B*8) >> 6
//Gray = (R*38 + G*75 + B*15) >> 7
//Gray = (R*76 + G*150 + B*30) >> 8
//Gray = (R*153 + G*300 + B*59) >> 9
//Gray = (R*306 + G*601 + B*117) >> 10
//Gray = (R*612 + G*1202 + B*234) >> 11
//Gray = (R*1224 + G*2405 + B*467) >> 12
//Gray = (R*2449 + G*4809 + B*934) >> 13
//Gray = (R*4898 + G*9618 + B*1868) >> 14
//Gray = (R*9797 + G*19235 + B*3736) >> 15
//Gray = (R*19595 + G*38469 + B*7472) >> 16
//Gray = (R*39190 + G*76939 + B*14943) >> 17
//Gray = (R*78381 + G*153878 + B*29885) >> 18
//Gray = (R*156762 + G*307757 + B*59769) >> 19
//Gray = (R*313524 + G*615514 + B*119538) >> 20
void
BurstLinker::grayScaleWeighted(const unsigned char *data, unsigned char *out, int width, int height, int channels) {
    uint32_t index = 0;
    uint32_t outIndex = 0;
    int r = 0;
    int g = 0;
    int b = 0;
    for (uint32_t i = 0; i < height; i++) {
        for (uint32_t j = 0; j < width; j++) {
            if (channels == 3) {
                r = data[index++];
                g = data[index++];
                b = data[index++];
            } else if (channels == 4) {
                r = data[index++];
                g = data[index++];
                b = data[index++];
                index++;
            } else {
                return;
            }
            // Gray = R*0.299 + G*0.587 + B*0.114
            out[outIndex++] = (r * 38 + g * 75 + b * 15) >> 7;
        }
    }
}

void BurstLinker::grayScaleAdobePhotoshop(const unsigned char *data, unsigned char *out, int width, int height,
                                          int channels) {
    uint32_t index = 0;
    uint32_t outIndex = 0;
    int r = 0;
    int g = 0;
    int b = 0;
    for (uint32_t i = 0; i < height; i++) {
        for (uint32_t j = 0; j < width; j++) {
            if (channels == 3) {
                r = data[index++];
                g = data[index++];
                b = data[index++];
            } else if (channels == 4) {
                r = data[index++];
                g = data[index++];
                b = data[index++];
                index++;
            } else {
                return;
            }
            // Gray = (R^2.2 * 0.2973 + G^2.2 * 0.6274 + B^2.2 * 0.0753)^(1/2.2)
            out[outIndex++] = std::pow(
                    (std::pow(r, 2.2) * 0.2973 + std::pow(g, 2.2) * 0.6274 + std::pow(b, 2.2) * 0.0753), 1 / 2.2);
        }
    }
}

void BurstLinker::grayScaleComponentR(const unsigned char *data, unsigned char *out, int width, int height,
                                      int channels) {
    uint32_t index = 0;
    uint32_t outIndex = 0;
    int r = 0;
    for (uint32_t i = 0; i < height; i++) {
        for (uint32_t j = 0; j < width; j++) {
            if (channels == 3) {
                r = data[index++];
                index++;
                index++;
            } else if (channels == 4) {
                r = data[index++];
                index++;
                index++;
                index++;
            } else {
                return;
            }
            out[outIndex++] = r;
        }
    }
}

void BurstLinker::grayScaleComponentG(const unsigned char *data, unsigned char *out, int width, int height,
                                      int channels) {
    uint32_t index = 0;
    uint32_t outIndex = 0;
    int g = 0;
    for (uint32_t i = 0; i < height; i++) {
        for (uint32_t j = 0; j < width; j++) {
            if (channels == 3) {
                index++;
                g = data[index++];
                index++;
            } else if (channels == 4) {
                index++;
                g = data[index++];
                index++;
                index++;
            } else {
                return;
            }
            out[outIndex++] = g;
        }
    }
}

void BurstLinker::grayScaleComponentB(const unsigned char *data, unsigned char *out, int width, int height,
                                      int channels) {
    uint32_t index = 0;
    uint32_t outIndex = 0;
    int b = 0;
    for (uint32_t i = 0; i < height; i++) {
        for (uint32_t j = 0; j < width; j++) {
            if (channels == 3) {
                index++;
                index++;
                b = data[index++];
            } else if (channels == 4) {
                index++;
                index++;
                b = data[index++];
                index++;
            } else {
                return;
            }
            out[outIndex++] = b;
        }
    }
}

void BurstLinker::grayScaleMax(const unsigned char *data, unsigned char *out, int width, int height, int channels) {
    uint32_t index = 0;
    uint32_t outIndex = 0;
    int r = 0;
    int g = 0;
    int b = 0;
    for (uint32_t i = 0; i < height; i++) {
        for (uint32_t j = 0; j < width; j++) {
            if (channels == 3) {
                r = data[index++];
                g = data[index++];
                b = data[index++];
            } else if (channels == 4) {
                r = data[index++];
                g = data[index++];
                b = data[index++];
                index++;
            } else {
                return;
            }
            out[outIndex++] = std::max(std::max(r, g), b);
        }
    }
}

void BurstLinker::grayScaleAverage(const unsigned char *data, unsigned char *out, int width, int height, int channels) {
    uint32_t index = 0;
    uint32_t outIndex = 0;
    int r = 0;
    int g = 0;
    int b = 0;
    for (uint32_t i = 0; i < height; i++) {
        for (uint32_t j = 0; j < width; j++) {
            if (channels == 3) {
                r = data[index++];
                g = data[index++];
                b = data[index++];
            } else if (channels == 4) {
                r = data[index++];
                g = data[index++];
                b = data[index++];
                index++;
            } else {
                return;
            }
            out[outIndex++] = r / 3 + g / 3 + b / 3;
        }
    }
}

void BurstLinker::grayScaleMaxMinAverage(const unsigned char *data, unsigned char *out, int width, int height,
                                         int channels) {
    uint32_t index = 0;
    uint32_t outIndex = 0;
    int r = 0;
    int g = 0;
    int b = 0;
    for (uint32_t i = 0; i < height; i++) {
        for (uint32_t j = 0; j < width; j++) {
            if (channels == 3) {
                r = data[index++];
                g = data[index++];
                b = data[index++];
            } else if (channels == 4) {
                r = data[index++];
                g = data[index++];
                b = data[index++];
                index++;
            } else {
                return;
            }
            int max = r;
            int min = r;
            if (g > max) {
                max = g;
            } else {
                min = g;
            }
            if (b > max) {
                max = b;
            } else if (b < min) {
                min = b;
            }
            out[outIndex++] = max / 2 + min / 2;
        }
    }
}

void BurstLinker::reverseColor(unsigned char *data, int width, int height, int channels) {
    uint32_t index = 0;
    for (uint32_t i = 0; i < height; i++) {
        for (uint32_t j = 0; j < width; j++) {
            for (int k = 0; k < channels; ++k) {
                data[index] = (255 - data[index]);
                index++;
            }
        }
    }
}

bool BurstLinker::connect(std::vector<uint32_t> &image, uint32_t delay,
                          QuantizerType quantizerType, DitherType ditherType, int32_t transparencyOption,
                          uint16_t left, uint16_t top) {
    if (gifEncoder == nullptr) {
        return false;
    }
    std::vector<uint8_t> content;
    gifEncoder->addImage(image, delay, quantizerType, ditherType, transparencyOption, left, top, content);
    gifEncoder->flush(content);
    return true;
}

bool BurstLinker::connect(std::vector<std::vector<uint32_t>> &images, uint32_t delay,
                          QuantizerType quantizerType, DitherType ditherType, int32_t transparencyOption,
                          uint16_t left, uint16_t top) {
    if (gifEncoder == nullptr) {
        return false;
    }
    size_t size = images.size();
    std::vector<std::future<std::vector<uint8_t>>> tasks;
    for (int k = 0; k < size; ++k) {
        auto result = gifEncoder->threadPool->enqueue([=, &images]() {
            std::vector<uint8_t> content;
            auto image = images[k];
            gifEncoder->addImage(image, delay, quantizerType, ditherType, transparencyOption, left, top, content);
            return content;
        });
        tasks.emplace_back(std::move(result));
    }
    for (auto &task : tasks) {
        std::vector<uint8_t> result = task.get();
        gifEncoder->flush(result);
    }
    return true;
}

void BurstLinker::release() {
    if (gifEncoder != nullptr) {
        gifEncoder->finishEncoding();
    }
}

