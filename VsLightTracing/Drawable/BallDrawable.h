//
// Created by memory4963 on 2017/5/28.
//
#pragma once

#ifndef LIGHTTRACING_BALLDRAWABLE_H
#define LIGHTTRACING_BALLDRAWABLE_H

#include "Drawable.h"
#include "BoxDrawable.h"

class BallDrawable : public Drawable {

private:
    float position[3];
    float radius;
public:

	BallDrawable *next;

    const float *getPosition() const;

    void setPosition(float x, float y, float z);

    float getRadius() const;

    void setRadius(float radius);

	BallDrawable();

    BoxDrawable generateBox();
};


#endif //LIGHTTRACING_BALLDRAWABLE_H
