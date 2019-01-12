//
// Created by succlz123 on 2017/11/30.
//

#ifndef BURSTLINKER_BURSTLINKER_H
#define BURSTLINKER_BURSTLINKER_H

#include <cstdint>
#include "GifEncoder.h"

namespace blk {

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


        bool connect(std::vector<uint32_t> &image, uint32_t delay,
                     QuantizerType quantizerType, DitherType ditherType, int32_t transparencyOption,
                     uint16_t left, uint16_t top);

        bool connect(std::vector<std::vector<uint32_t >> &images, uint32_t delay,
                     QuantizerType quantizerType, DitherType ditherType, int32_t transparencyOption,
                     uint16_t left, uint16_t top);

        void release();

    private:

        std::unique_ptr<GifEncoder> gifEncoder;

    };

}

#endif //BURSTLINKER_BURSTLINKER_H
