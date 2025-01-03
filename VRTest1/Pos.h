#pragma once
class Pos
{
	public:
		Pos(float* x, float* y, float* z, float* yaw, float* pitch, float* roll);
		Pos(float* x, float* y, float* z);
		Pos(float x, float y, float z, float yaw, float pitch, float roll, bool permmode);
		Pos(float x, float y, float z, bool permmode);
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
		float xperm;
		float yperm;
		float zperm;
		float yawperm;
		float pitchperm;
		float rollperm;
		bool permmode = false;
};

