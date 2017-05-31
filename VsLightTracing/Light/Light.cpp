//
// Created by memory4963 on 2017/5/28.
//

#include "Light.h"

const float *Light::getPosition() const {
    return position;
}

const float *Light::getRgb() const {
    return rgb;
}

void Light::setPosition(float x, float y, float z) {
    Light::position[0] = x;
    Light::position[1] = y;
    Light::position[2] = z;
}

void Light::setRGB(float r, float g, float b) {
    Light::rgb[0] = r;
    Light::rgb[1] = g;
    Light::rgb[2] = b;
}
