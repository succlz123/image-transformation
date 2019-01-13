//
// Created by succlz123 on 19-1-13.
//

#include <cmath>
#include "SpotlightFilter.h"

using namespace it;

double getDistance(int centerX, int centerY, int px, int py) {
    double xx = (centerX - px) * (centerX - px);
    double yy = (centerY - py) * (centerY - py);
    return (int) std::sqrt(xx + yy);
}

void SpotlightFilter::filter(unsigned char *data, int width, int height, int channels) {
    int offset = 0;
    int centerX = width / 2;
    int centerY = height / 2;
    double maxDistance = std::sqrt(centerX * centerX + centerY * centerY);

    int index = 0;
    int outIndex = 0;
    int r = 0;
    int g = 0;
    int b = 0;
    for (int i = 0; i < height; i++) {
        index = i * width * channels;
        for (int j = 0; j < width; j++) {
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

            double scale = 1.0 - getDistance(centerX, centerY, j, i) / maxDistance;
            for (int k = 0; k < factor; k++) {
                scale = scale * scale;
            }

            r = (int) (scale * r);
            g = (int) (scale * g);
            b = (int) (scale * b);

            if (channels >= 3) {
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
