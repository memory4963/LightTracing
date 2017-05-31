//
// Created by memory4963 on 2017/5/28.
//
#pragma once

#ifndef LIGHTTRACING_RAY_H
#define LIGHTTRACING_RAY_H


class Ray {
protected:
    float brightness;
    float direction[3];
    float position[3];
public:
    float getBrightness() const;

    void setBrightness(float brightness);

    const float *getDirection() const;

    const float *getPosition() const;

    void setDirection(float x, float y, float z);

    void setPosition(float x, float y, float z);
};


#endif //LIGHTTRACING_RAY_H
