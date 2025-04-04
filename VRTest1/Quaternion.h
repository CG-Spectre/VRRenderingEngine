#pragma once
#include "Vector3.h"
struct Quaternion
{
	public:
		Quaternion(float yaw, float pitch, float roll);
		float yaw;
		float pitch;
		float roll;
		Vector3 getNormalizedVector();
};

