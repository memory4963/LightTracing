//
// Created by memory4963 on 2017/5/28.
//
#pragma once

#ifndef LIGHTTRACING_GENERATEIMAGE_H
#define LIGHTTRACING_GENERATEIMAGE_H

#include "Drawable/BallDrawable.h"
#include "Light/PointLight.h"

#define PORT 800
#define BG_DIR 10


class GenerateImage {
public:
    void generate();
	~GenerateImage();

private:

    FILE *bFile;
    FILE *wFile;

	float O[3];
	double *viewVertex;
    double *point;
    double *color;

    BallDrawable headPointer;
    BallDrawable secBall;
    BallDrawable firBall;
	BallDrawable mirBall;

    PointLight pointLight;

    void readBaseImage();

    void openWriteImage();

    void setThings();

	void lightTracing(double * V, double t, double * color, BallDrawable *ball, int iteration);

	bool judgeShield(double * V, double t, BallDrawable * ball);

	void diffuseSpecular(double * V, double t, double * color, int k, BallDrawable *ball);

	void mirror(double * V, double t, double * color, BallDrawable *ball, int iteration);

    void generateImage();
};


#endif //LIGHTTRACING_GENERATEIMAGE_H
