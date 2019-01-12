//
// Created by succlz123 on 17-9-12.
//

#ifndef BURSTLINKER_UNIFORMQUANTIZER_H
#define BURSTLINKER_UNIFORMQUANTIZER_H

#include "ColorQuantizer.h"

namespace blk {

    class SepiaToneFilter {

    public:

        void filter(unsigned char *data, int width, int height, int channels);
    };

}

#endif //BURSTLINKER_UNIFORMQUANTIZER_H
