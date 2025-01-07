#include "Pos2D.h"
#include <cmath>

Pos2D::Pos2D(int x, int y) : x(x), y(y)
{
}

int Pos2D::getX()
{
	return this->x;
}

int Pos2D::getY()
{
	return this->y;
}

void Pos2D::setX(int x)
{
	this->x = x;
}

void Pos2D::setY(int y)
{
	this->y = y;
}

float Pos2D::calcDistance(Pos2D pos1, Pos2D pos2) {
	return sqrtf(powf(pos1.getX() - pos2.getX(), 2) + powf(pos1.getY() - pos2.getY(), 2));
}
