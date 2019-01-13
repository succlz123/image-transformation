//
// Created by succlz123 on 19-1-13.
//

#ifndef BURSTLINKER_SPOTLIGHTFILTER_H
#define BURSTLINKER_SPOTLIGHTFILTER_H


namespace it {

    class SpotlightFilter {

    public:

        int factor = 1;

        void filter(unsigned char *data, int width, int height, int channels);
    };
}

#endif //BURSTLINKER_SPOTLIGHTFILTER_H
