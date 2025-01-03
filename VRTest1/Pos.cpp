#include "Pos.h"
#include <cstddef>

Pos::Pos(float* x, float* y, float* z, float* yaw, float* pitch, float* roll) : x(x), y(y), z(z), pitch(pitch), roll(roll), yaw(yaw) {
	xperm = NULL;
	yperm = NULL;
	zperm = NULL;
	yawperm = NULL;
	pitchperm = NULL;
	rollperm = NULL;
}

Pos::Pos(float* x, float* y, float* z) : x(x), y(y), z(z), pitch(0), roll(0), yaw(0) {
	xperm = NULL;
	yperm = NULL;
	zperm = NULL;
	yawperm = NULL;
	pitchperm = NULL;
	rollperm = NULL;
}

Pos::Pos(float x, float y, float z, float yaw, float pitch, float roll, bool permmode) : xperm(x), yperm(y), zperm(z), pitchperm(pitch), rollperm(roll), yawperm(yaw) {
	this->x = nullptr;
	this->y = nullptr;
	this->z = nullptr;
	this->yaw = nullptr;
	this->pitch = nullptr;
	this->roll = nullptr;
	this->permmode = true;
}

Pos::Pos(float x, float y, float z, bool permmode) : xperm(x), yperm(y), zperm(z), pitchperm(0), rollperm(0), yawperm(0) {
	this->x = nullptr;
	this->y = nullptr;
	this->z = nullptr;
	this->yaw = nullptr;
	this->pitch = nullptr;
	this->roll = nullptr;
	this->permmode = true;
}

void Pos::setX(float val) {
	this->x = &val;
}

void Pos::setY(float val) {
	this->y = &val;
}

float* Pos::getX() {
	if (permmode) {
		return &this->xperm;
	}
	return this->x;
}

float* Pos::getY() {
	if (permmode) {
		return &this->yperm;
	}
	return this->y;
}

float* Pos::getZ()
{
	if (permmode) {
		return &this->zperm;
	}
	return this->z;
}
float* Pos::getPitch()
{
	if (permmode) {
		return &this->pitchperm;
	}
	return this->pitch;
}
float* Pos::getYaw()
{
	if (permmode) {
		return &this->yawperm;
	}
	return this->yaw;
}
float* Pos::getRoll()
{
	if (permmode) {
		return &this->rollperm;
	}
	return this->roll;
}
