//
// Created by memory4963 on 2017/5/28.
//

#include "Drawable.h"

float Drawable::getDiffuse() const {
    return diffuse;
}

void Drawable::setDiffuse(float diffuse) {
    Drawable::diffuse = diffuse;
}

float Drawable::getSpecular() const {
    return specular;
}

void Drawable::setSpecular(float specular) {
    Drawable::specular = specular;
}

float Drawable::getAmbient() const {
    return ambient;
}

void Drawable::setAmbient(float ambient) {
    Drawable::ambient = ambient;
}

Drawable::Drawable() {
    Drawable::diffuse = 0.6;
    Drawable::specular = 0.4;
    Drawable::ambient = 0.2;
	Drawable::mirror = 0;
}

DrawableEnum Drawable::getType()
{
	return type;
}

void Drawable::setMirror(bool mirror)
{
	Drawable::mirror = mirror;
}

const bool Drawable::getMirror()
{
	return mirror;
}

const float *Drawable::getRgb() const {
    return rgb;
}

void Drawable::setRgb(float r, float g, float b) {
    Drawable::rgb[0] = r;
    Drawable::rgb[1] = g;
    Drawable::rgb[2] = b;
}
