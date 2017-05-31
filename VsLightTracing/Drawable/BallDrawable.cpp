//
// Created by memory4963 on 2017/5/28.
//

#include "BallDrawable.h"

//BoxDrawable BallDrawable::generateBox() {
//    return BoxDrawable(BallDrawable::position[0] - BallDrawable::radius,
//                       BallDrawable::position[1] - BallDrawable::radius,
//                       BallDrawable::position[2] - BallDrawable::radius,
//                       BallDrawable::position[0] + BallDrawable::radius,
//                       BallDrawable::position[1] + BallDrawable::radius,
//                       BallDrawable::position[2] + BallDrawable::radius);
//}

const float *BallDrawable::getPosition() const {
    return position;
}

float BallDrawable::getRadius() const {
    return radius;
}

void BallDrawable::setRadius(float radius) {
    BallDrawable::radius = radius;
}

BallDrawable::BallDrawable() :Drawable()
{
	type = Ball;
}

BoxDrawable BallDrawable::generateBox()
{
	return BoxDrawable(getPosition()[0] - getRadius(), getPosition()[1] - getRadius(), getPosition()[2] - getRadius(),
		getPosition()[0] + getRadius(), getPosition()[1] + getRadius(), getPosition()[2] + getRadius());
}

void BallDrawable::setPosition(float x, float y, float z) {
    BallDrawable::position[0] = x;
    BallDrawable::position[1] = y;
    BallDrawable::position[2] = z;
}
