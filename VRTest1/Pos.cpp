#include "Pos.h"

Pos::Pos(float* x, float* y, float* z, float* yaw, float* pitch, float* roll) : x(x), y(y), z(z), pitch(pitch), roll(roll), yaw(yaw) {
	
}

void Pos::setX(float val) {
	this->x = &val;
}

void Pos::setY(float val) {
	this->y = &val;
}

float* Pos::getX() {
	return this->x;
}

float* Pos::getY() {
	return this->y;
}

float* Pos::getZ()
{
	return this->z;
}
float* Pos::getPitch()
{
	return this->pitch;
}
float* Pos::getYaw()
{
	return this->yaw;
}
float* Pos::getRoll()
{
	return this->roll;
}
