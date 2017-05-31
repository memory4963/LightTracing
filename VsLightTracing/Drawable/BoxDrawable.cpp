//
// Created by memory4963 on 2017/5/28.
//

#include "BoxDrawable.h"

const float *BoxDrawable::getPosition() const {
    return position;
}

void BoxDrawable::setPostion(float x1, float y1, float z1, float x2, float y2, float z2) {
    BoxDrawable::position[0] = x1;
    BoxDrawable::position[1] = y1;
    BoxDrawable::position[2] = z1;
    BoxDrawable::position[3] = x2;
    BoxDrawable::position[4] = y2;
    BoxDrawable::position[5] = z2;
}

BoxDrawable::BoxDrawable(float x1, float y1, float z1, float x2, float y2, float z2){
    BoxDrawable::position[0] = x1;
    BoxDrawable::position[1] = y1;
    BoxDrawable::position[2] = z1;
    BoxDrawable::position[3] = x2;
    BoxDrawable::position[4] = y2;
    BoxDrawable::position[5] = z2;
}
