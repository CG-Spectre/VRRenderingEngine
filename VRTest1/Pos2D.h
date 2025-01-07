#pragma once
class Pos2D
{
	public:
		Pos2D(int x, int y);
		int getX();
		int getY();
		void setX(int x);
		void setY(int y);
		static float calcDistance(Pos2D pos1, Pos2D pos2);
	private:
		int x;
		int y;
};

