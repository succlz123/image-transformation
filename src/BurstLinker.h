//
// Created by succlz123 on 2017/11/30.
//

#ifndef BURSTLINKER_BURSTLINKER_H
#define BURSTLINKER_BURSTLINKER_H

#include <cstdint>
#include "GifEncoder.h"

namespace it {

    class BurstLinker {

    public:

        void grayScaleWeighted(const unsigned char *data, unsigned char *out, int width, int height, int channels);

        void
        grayScaleAdobePhotoshop(const unsigned char *data, unsigned char *out, int width, int height, int channels);

        void grayScaleComponentR(const unsigned char *data, unsigned char *out, int width, int height, int channels);

        void grayScaleComponentG(const unsigned char *data, unsigned char *out, int width, int height, int channels);

        void grayScaleComponentB(const unsigned char *data, unsigned char *out, int width, int height, int channels);

        void grayScaleMax(const unsigned char *data, unsigned char *out, int width, int height, int channels);

        void grayScaleAverage(const unsigned char *data, unsigned char *out, int width, int height, int channels);

        void grayScaleMaxMinAverage(const unsigned char *data, unsigned char *out, int width, int height, int channels);

        void reverseColor(unsigned char *data, int width, int height, int channels);

        void sepiaToneFilter(unsigned char *data, int width, int height, int channels);

        void whiteImageFilter(unsigned char *data, int width, int height, int channels);

        void spotlightFilter(unsigned char *data, int width, int height, int channels);

    private:

        std::unique_ptr<GifEncoder> gifEncoder;

    };

}

#endif //BURSTLINKER_BURSTLINKER_H
