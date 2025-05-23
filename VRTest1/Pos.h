#pragma once
#include "Vector3.h"
class Pos
{
	public:
		explicit Pos(float* x, float* y, float* z, float* yaw, float* pitch, float* roll);
		explicit Pos(float* x, float* y, float* z);
		explicit Pos(float x, float y, float z, float yaw, float pitch, float roll);
		explicit Pos(float x, float y, float z);
		void setX(float val);
		void setY(float val);
		void setZ(float val);
		void setYaw(float val);
		void setPitch(float val);
		void setRoll(float val);
		float* getX();
		float* getY();
		float* getZ();
		float* getYaw();
		float* getPitch();
		float* getRoll();
		Vector3 getAsVector3();
		Vector3 getNormalizedRotation();
	private:
		float x;
		float y;
		float z;
		float yaw;
		float pitch;
		float roll;
};

