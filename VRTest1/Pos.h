#pragma once
class Pos
{
	public:
		Pos(float* x, float* y, float* z, float* yaw, float* pitch, float* roll);
		void setX(float val);
		void setY(float val);
		float* getX();
		float* getY();
		float* getZ();
		float* getYaw();
		float* getPitch();
		float* getRoll();
	private:
		float* x;
		float* y;
		float* z;
		float* yaw;
		float* pitch;
		float* roll;
};

