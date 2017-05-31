//
// Created by memory4963 on 2017/5/28.
//
#pragma once

#ifndef LIGHTTRACING_DRAWABLE_H
#define LIGHTTRACING_DRAWABLE_H

#include "BoxDrawable.h"

enum DrawableEnum
{
	Ball, Box, Plat
};

class Drawable {
protected:
	bool mirror;
    /**
     * 漫反射
     */
    float diffuse;
    /**
    * 镜面反射
    */
    float specular;
    /**
     * 环境光
     */
    float ambient;

    float rgb[3];

	DrawableEnum type;

public:

	//virtual BoxDrawable generateBox() = 0;

	Drawable();

	DrawableEnum getType();

	void setMirror(bool mirror);

	const bool getMirror();

    const float *getRgb() const;

    void setRgb(float r, float g, float b);

    float getDiffuse() const;

    void setDiffuse(float diffuse);

    float getSpecular() const;

    void setSpecular(float specular);

    float getAmbient() const;

    void setAmbient(float ambient);

//    virtual BoxDrawable generateBox();

};


#endif //LIGHTTRACING_DRAWABLE_H
