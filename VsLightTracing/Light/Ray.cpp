//
// Created by memory4963 on 2017/5/28.
//

#include "Ray.h"

float Ray::getBrightness() const {
    return brightness;
}

void Ray::setBrightness(float brightness) {
    Ray::brightness = brightness;
}

const float *Ray::getDirection() const {
    return direction;
}

const float *Ray::getPosition() const {
    return position;
}

void Ray::setDirection(float x, float y, float z) {
    Ray::direction[0] = x;
    Ray::direction[1] = y;
    Ray::direction[2] = z;
}

void Ray::setPosition(float x, float y, float z) {
    Ray::position[0] = x;
    Ray::position[1] = y;
    Ray::position[2] = z;
}
