//
// Created by succlz123 on 2017/11/10.
//

#ifndef BURSTLINKER_DITHERERWITHRS_H
#define BURSTLINKER_DITHERERWITHRS_H

#include "../../../../../src/Ditherer.h"
#include <RenderScript.h>

class DithererWithRs : public it::Ditherer {

public:

    void
    dither(it::RGB *originPixels, uint16_t width, uint16_t height,
           it::RGB quantizerPixels[], int32_t quantizerSize,
           uint8_t *colorIndices) {};

    virtual void
    dither(it::RGB *originPixels, uint16_t width, uint16_t height,
           it::RGB quantizerPixels[], int32_t quantizerSize,
           uint8_t *colorIndices, android::RSC::sp<android::RSC::RS> rs)=0;

};


#endif //BURSTLINKER_DITHERERWITHRS_H
