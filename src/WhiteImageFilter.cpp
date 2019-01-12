//
// Created by succlz123 on 17-9-12.
//

#include <cmath>
#include <cstring>
#include <iostream>
#include <random>
#include "WhiteImageFilter.h"

using namespace blk;

int imageMath(int gray, double beta) {
    double scale = 255 / (std::log(255 * (beta - 1) + 1) / std::log(beta));
    double p1 = std::log(gray * (beta - 1) + 1);
    double np = p1 / std::log(beta);
    return (int) (np * scale);
}

void WhiteImageFilter::filter(unsigned char *data, int width, int height, int channels) {
    int lut[256];
    for (int i = 0; i < 256; i++) {
        lut[i] = imageMath(i, beta);
    }
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
            if (channels >= 3) {
                data[outIndex++] = lut[r];
                data[outIndex++] = lut[g];
                data[outIndex++] = lut[b];
                if (channels == 4) {
                    outIndex++;
                }
            }
        }
    }
}
