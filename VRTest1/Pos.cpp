#include "Pos.h"
#include <cstddef>
#include "Quaternion.h"

Pos::Pos(float* x, float* y, float* z, float* yaw, float* pitch, float* roll) : x(*x), y(*y), z(*z), pitch(*pitch), roll(*roll), yaw(*yaw) {
	
}

Pos::Pos(float* x, float* y, float* z) : x(*x), y(*y), z(*z), pitch(0), roll(0), yaw(0) {
	
}

Pos::Pos(float x, float y, float z, float yaw, float pitch, float roll) : x(x), y(y), z(z), pitch(pitch), roll(roll), yaw(yaw) {
	
}

Pos::Pos(float x, float y, float z) : x(x), y(y), z(z), pitch(0), roll(0), yaw(0) {
	
}

void Pos::setX(float val) {
	this->x = val;
}

void Pos::setY(float val) {
	this->y = val;
}

void Pos::setZ(float val)
{
	this->z = val;
}

void Pos::setYaw(float val)
{
	this->yaw = val;
}

void Pos::setPitch(float val)
{
	this->pitch = val;
}

void Pos::setRoll(float val)
{
	this->roll = val;
}


float* Pos::getX() {
	return &this->x;
}

float* Pos::getY() {
	return &this->y;
}

float* Pos::getZ()
{
	return &this->z;
}
float* Pos::getPitch()
{
	return &this->pitch;
}
float* Pos::getYaw()
{
	return &this->yaw;
}
float* Pos::getRoll()
{
	return &this->roll;
}

Vector3 Pos::getAsVector3() {
	return Vector3(x, y, z);
}

Vector3 Pos::getNormalizedRotation()
{
	return Quaternion(yaw, pitch, roll).getNormalizedVector();
}
