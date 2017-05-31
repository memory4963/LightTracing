//
// Created by memory4963 on 2017/5/28.
//
#pragma once

#ifndef LIGHTTRACING_LIGHT_H
#define LIGHTTRACING_LIGHT_H

class Light {
protected:
    float position[3];
    float rgb[3];
public:
    const float *getPosition() const;

    const float *getRgb() const;

    void setPosition(float x, float y, float z);

    void setRGB(float r, float g, float b);
};


#endif //LIGHTTRACING_LIGHT_H
