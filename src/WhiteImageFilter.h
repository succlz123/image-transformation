//
// Created by succlz123 on 17-9-12.
//

#ifndef BURSTLINKER_WhiteImageFilter_H
#define BURSTLINKER_WhiteImageFilter_H

namespace it {

    class WhiteImageFilter {

    public:

        double beta = 1.1;

        void filter(unsigned char *data, int width, int height, int channels);
    };

}

#endif //BURSTLINKER_WhiteImageFilter_H
