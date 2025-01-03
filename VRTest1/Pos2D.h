#pragma once
class Pos2D
{
	public:
		Pos2D(int x, int y);
		int getX();
		int getY();
		void setX(int x);
		void setY(int y);
	private:
		int x;
		int y;
};

