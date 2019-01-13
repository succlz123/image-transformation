//
// Created by succlz123 on 17-9-12.
//

#include <cmath>
#include <cstring>
#include <iostream>
#include <random>
#include "SepiaToneFilter.h"

using namespace it;

double randZeroToOne() {
    return rand() / (RAND_MAX + 1.);
}

double noise() {
    auto zi = randZeroToOne() * 0.5 + 0.5;
    return zi;
}

double colorBlend(double scale, double dest, double src) {
    return (scale * dest + (1.0 - scale) * src);
}

void SepiaToneFilter::filter(unsigned char *data, int width, int height, int channels) {
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
                r = (int) colorBlend(noise(), (r * 0.393) + (g * 0.769) + (b * 0.189), r);
                g = (int) colorBlend(noise(), (r * 0.349) + (g * 0.686) + (b * 0.168), g);
                b = (int) colorBlend(noise(), (r * 0.272) + (g * 0.534) + (b * 0.131), b);
                data[outIndex++] = r;
                data[outIndex++] = g;
                data[outIndex++] = b;
                if (channels == 4) {
                    outIndex++;
                }
            }
        }
    }
}
