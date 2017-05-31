//
// Created by memory4963 on 2017/5/28.
//
#pragma once

#ifndef LIGHTTRACING_BOXDRAWABLE_H
#define LIGHTTRACING_BOXDRAWABLE_H

class BoxDrawable {

private:
    /**
     * x1,y1,z1,x2,y2,z2
     */
    float position[6];
public:
    const float *getPosition() const;

    void setPostion(float x1, float y1, float z1, float x2, float y2, float z2);

    BoxDrawable(float x1, float y1, float z1, float x2, float y2, float z2);

};


#endif //LIGHTTRACING_BOXDRAWABLE_H
