#include "Pos2D.h"

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
