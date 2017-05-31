//
// Created by memory4963 on 2017/5/28.
//

#define _CRT_SECURE_NO_WARNINGS

#include <cstdio>
#include <cstdlib>
#include <cmath>
#include "GenerateImage.h"

void GenerateImage::readBaseImage() {
    //800*800
    if ((bFile = fopen("base.bmp", "rb")) == NULL) {
        printf("read base.bmp failed.");
        exit(0);
    }
}

void GenerateImage::openWriteImage() {
    if ((wFile = fopen("output.bmp", "wb")) == NULL) {
        fclose(bFile);
        printf("load output.bmp failed.");
        exit(0);
    }
    unsigned char header[54];
    fread(header, 54, 1, bFile);
    fwrite(header, 54, 1, wFile);
}

void GenerateImage::generate() {

	O[0] = 0;
	O[1] = 0;
	O[2] = 2;
    viewVertex = new double[PORT * PORT * 3];
    point = new double[PORT * PORT];
    color = new double[PORT * PORT * 3];

    //文件准备
    readBaseImage();
    openWriteImage();

    // 光线跟踪，视口大小800*800
    // 视点(0,0,2)
    // 前视窗(0,0,0)
    // 后视窗(0,0,-2)
	int i1 = 320, j1 = 520;
    for (int i = 0; i < PORT; ++i) {
        for (int j = 0; j < PORT; ++j) {
			viewVertex[i * PORT * 3 + j * 3 + 0] = (2.0 / PORT * (j - (PORT / 2)) - O[0]) /
				sqrt(2.0 / PORT * (j - (PORT / 2) - O[0])*(2.0 / PORT * (j - (PORT / 2)) - O[0]) +
				(2.0 / PORT * ((PORT / 2) - i) - O[1])*(2.0 / PORT * ((PORT / 2) - i) - O[1]) + (-O[2])*(-O[2]));
            viewVertex[i * PORT * 3 + j * 3 + 1] = (2.0 / PORT * ((PORT / 2) - i) - O[1]) /
				sqrt(2.0 / PORT * (j - (PORT / 2) - O[0])*(2.0 / PORT * (j - (PORT / 2)) - O[0]) +
				(2.0 / PORT * ((PORT / 2) - i) - O[1])*(2.0 / PORT * ((PORT / 2) - i) - O[1]) + (-O[2])*(-O[2]));
            viewVertex[i * PORT * 3 + j * 3 + 2] = (-O[2]) /
				sqrt(2.0 / PORT * (j - (PORT / 2) - O[0])*(2.0 / PORT * (j - (PORT / 2)) - O[0]) +
				(2.0 / PORT * ((PORT / 2) - i) - O[1])*(2.0 / PORT * ((PORT / 2) - i) - O[1]) + (-O[2])*(-O[2]));

			if (i == 320 && j == 520)
			{
				printf("....");
			}

            point[i * PORT + j] = BG_DIR;

            for (int k = 0; k < 3; ++k) {
				color[i * PORT * 3 + j * 3 + k] = 0;
            }
        }
    }

    setThings();

    BallDrawable *p;
    BallDrawable *ball = NULL;

    for (int i = 0; i < PORT; ++i) {
        for (int j = 0; j < PORT; ++j) {
            p = &headPointer;
			bool trace = false;
			while (p->next != NULL) {
                p = p->next;

                //球求交，包围盒改进
                double a = viewVertex[i * PORT * 3 + j * 3 + 0] * viewVertex[i * PORT * 3 + j * 3 + 0]
                           + viewVertex[i * PORT * 3 + j * 3 + 1] * viewVertex[i * PORT * 3 + j * 3 + 1]
                           + viewVertex[i * PORT * 3 + j * 3 + 2] * viewVertex[i * PORT * 3 + j * 3 + 2];
                double b = 2 * (viewVertex[i * PORT * 3 + j * 3 + 0] * (O[0] - p->getPosition()[0])
                                + viewVertex[i * PORT * 3 + j * 3 + 1] * (O[1] - p->getPosition()[1])
                                + viewVertex[i * PORT * 3 + j * 3 + 2] * (O[2] - p->getPosition()[2]));
                double c = ((O[0] - p->getPosition()[0]) * (O[0] - p->getPosition()[0])
                            + (O[1] - p->getPosition()[1]) * (O[1] - p->getPosition()[1])
                            + (O[2] - p->getPosition()[2]) * (O[2] - p->getPosition()[2]))
                           - p->getRadius() * p->getRadius();
                double derta = b * b - 4 * a * c;
				if (i == 400 && j == 400)
				{
					printf("....");
				}
                if (derta >= 0) {
                    double x = (-b - sqrt(derta)) / 2 * a;
                    if (x < point[i * PORT + j]) {
                        point[i * PORT + j] = x;
                        ball = p;
						trace = true;
                    }
                }
            }

			if (trace)
			{
				double V[3];
				double t;
				t = point[i*PORT + j];
				for (size_t k = 0; k < 3; k++)
				{
					V[k] = viewVertex[i*PORT * 3 + j * 3 + k];
				}
				lightTracing(V, t, &color[i*PORT * 3 + j * 3], ball, 1);
			}

        }
    }

    generateImage();

}

void GenerateImage::lightTracing(double * V, double t, double * color, BallDrawable *ball, int iteration) {

    if (t == BG_DIR || ball == NULL || iteration == 0) {
        return;
    }

	// 如有镜面反射进入迭代
	if (ball->getMirror())
	{
		mirror(V, t, color, ball, iteration);
		return;
	}

    // 判断遮挡
	bool shield = judgeShield(V, t, ball);
    // 处理光线
    for (int k = 0; k < 3; ++k) {
        color[k] += ball->getRgb()[k] * ball->getAmbient();
		if (!shield)
		{
			diffuseSpecular(V, t, color, k, ball);
		}
    }
}

bool GenerateImage::judgeShield(double * V, double t, BallDrawable * ball)
{
	float P[3];

	for (size_t k = 0; k < 3; k++)
	{
		P[k] = O[k] + t * V[k];
	}
	float V1[3];
	for (size_t k = 0; k < 3; k++)
	{
		V1[k] = (pointLight.getPosition()[k] - P[k]) / sqrt((pointLight.getPosition()[0] - P[0])*(pointLight.getPosition()[0] - P[0])
			+ (pointLight.getPosition()[1] - P[1])*(pointLight.getPosition()[1] - P[1])
			+ (pointLight.getPosition()[2] - P[2])*(pointLight.getPosition()[2] - P[2]));
	}
	BallDrawable *p = &headPointer;
	while (p->next != NULL)
	{
		p = p->next;
		if (p == ball)
		{
			continue;
		}
		float a = V1[0] * V1[0] + V1[1] * V1[1] + V1[2] * V1[2];
		float b = 2 * (V1[0] * (P[0] - p->getPosition()[0])
			+ V1[1] * (P[1] - p->getPosition()[1])
			+ V1[2] * (P[2] - p->getPosition()[2]));
		float c = ((P[0] - p->getPosition()[0])*(P[0] - p->getPosition()[0])
			+ (P[1] - p->getPosition()[1])*(P[1] - p->getPosition()[1])
			+ (P[2] - p->getPosition()[2])*(P[2] - p->getPosition()[2]))
			- p->getRadius()*p->getRadius();
		float derta = b*b - 4 * a*c;
		if (derta >= 0)
		{
			double x1 = (-b + sqrt(derta)) / 2 * a;
			double x2 = (-b - sqrt(derta)) / 2 * a;
			if ((x1 > 0 && x1 < 1) || (x2 > 0 && x2 < 1))
			{
				return true;
			}
		}
	}
	//判断遮挡
	
	return false;
}

void GenerateImage::diffuseSpecular(double * V, double t, double * color, int k, BallDrawable *ball)
{
	float P[3];
	for (size_t i1 = 0; i1 < 3; i1++)
	{
		P[i1] = O[i1] + t * V[i1];
	}
	float N[3];
	for (size_t i1 = 0; i1 < 3; i1++)
	{
		N[i1] = (P[i1] - ball->getPosition()[i1]) / ball->getRadius();
	}
	//多光源循环
	float L[3];
	for (size_t i1 = 0; i1 < 3; i1++)
	{
		L[i1] = (pointLight.getPosition()[i1] - P[i1]) / sqrt((pointLight.getPosition()[0] - P[0])* (pointLight.getPosition()[0] - P[0])
			+ (pointLight.getPosition()[1] - P[1])* (pointLight.getPosition()[1] - P[1])
			+ (pointLight.getPosition()[2] - P[2])* (pointLight.getPosition()[2] - P[2]));
	}
	float LN = N[0] * L[0] + N[1] * L[1] + N[2] * L[2];
	if (LN >= 0)
	{
		//diffuse
		color[k] += ball->getRgb()[k] * ball->getDiffuse()*LN;
		//specular
		float V1[3];
		for (size_t i1 = 0; i1 < 3; i1++)
		{
			V1[i1] = O[i1] - P[i1];
		}
		float H[3];
		for (size_t i1 = 0; i1 < 3; i1++)
		{
			H[i1] = (L[i1] + V1[i1]) / sqrt((L[0] + V1[0])*(L[0] + V1[0]) + (L[1] + V1[1])*(L[1] + V1[1]) + (L[2] + V1[2])*(L[2] + V1[2]));
		}
		float NH = N[0] * H[0] + N[1] * H[1] + N[2] * H[2];
		if (NH >= 1 / sqrt(2))
		{
			color[k] += ball->getRgb()[k] * ball->getSpecular()*pow(cos(2 * acos(NH)), 30);
		}
	}

}

void GenerateImage::mirror(double * V, double t, double * color, BallDrawable *ball, int iteration)
{
	float P[3];
	for (size_t k = 0; k < 3; k++)
	{
		P[k] = O[k] + t * V[k];
	}
	float N[3];
	for (size_t k = 0; k < 3; k++)
	{
		N[k] = (P[k] - ball->getPosition()[k]) / ball->getRadius();
	}
	float L[3];
	for (size_t k = 0; k < 3; k++)
	{
		L[k] = -V[k];
	}
	float NL = L[0] * N[0] + L[1] * N[1] + L[2] * N[2];
	float V1[3];
	for (size_t k = 0; k < 3; k++)
	{
		V1[k] = L[k] - 2 * N[k] * NL;
	}

	//球求交
	float t1 = 10000;
	BallDrawable *p = &headPointer;
	while (p->next != NULL)
	{
		p = p->next;

	}
	//光源
	

}

void GenerateImage::setThings() {
	headPointer.next = &firBall;
	firBall.next = &secBall;
	//secBall.next = &mirBall;

	firBall.setRadius(0.2);
	firBall.setPosition(0.7, 0.2, -0.8);
	firBall.setRgb(0.2, 0.2, 0.9);
	firBall.setSpecular(1);

	secBall.setRadius(0.2);
	secBall.setSpecular(0.9);
	secBall.setDiffuse(0.1);
	secBall.setPosition(0.3, 0.2, -0.92);
	secBall.setRgb(0.6, 1, 0.3);

	mirBall.setMirror(true);
	

	pointLight.setPosition(-1, 0.2, -0.8);
	pointLight.setRGB(1, 1, 1);
}

void GenerateImage::generateImage() {
    int *colorInt = new int[PORT * PORT * 3];
    for (int i = 0; i < PORT; ++i) {
        for (int j = 0; j < PORT; ++j) {
            for (int k = 2; k > -1; --k) {
				colorInt[i * PORT * 3 + j * 3 + k] = (int)(color[i * PORT * 3 + j * 3 + k] * 255 + 0.5);
				if (colorInt[i * PORT * 3 + j * 3 + k] > 255)
				{
					colorInt[i * PORT * 3 + j * 3 + k] = 255;
				}
				else if (colorInt[i * PORT * 3 + j * 3 + k] < 0)
				{
					colorInt[i * PORT * 3 + j * 3 + k] = 0;
				}
                fwrite(&colorInt[i * PORT * 3 + j * 3 + k], 1, 1, wFile);
				if (i == 320 && j == 520)
				{
					printf(".....");
				}
            }
        }
    }

    delete colorInt;

    fclose(wFile);
    fclose(bFile);

}

GenerateImage::~GenerateImage()
{
	delete point, viewVertex, color;
}