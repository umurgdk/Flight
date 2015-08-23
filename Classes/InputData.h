//
// Created by Umur Gedik on 22/08/15.
//

#ifndef FLIGHT_INPUTDATA_H
#define FLIGHT_INPUTDATA_H

#include "cocos2d.h"

namespace Flight {
    typedef struct InputData {
        cocos2d::Vec2 pointerPosition{0.0f, 0.0f};
        bool pointerIsDown{false};
    } InputData;
}

#endif //FLIGHT_INPUTDATA_H
