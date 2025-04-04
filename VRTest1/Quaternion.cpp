
#include "Quaternion.h"
#include "cmath"
#include <SDL_stdinc.h>

Quaternion::Quaternion(float yaw, float pitch, float roll) : yaw(yaw), pitch(pitch), roll(roll)
{
}

Vector3 Quaternion::getNormalizedVector()
{
	float toRadians = (M_PI / 180);
	float pitchRad = toRadians * pitch;
	float rollRad = toRadians * roll;
	float yawRad = toRadians * yaw;
	return Vector3(
		std::cos(pitchRad) * std::cos(yawRad), 
		std::sin(rollRad) * std::sin(yawRad) - std::cos(rollRad) * std::sin(pitchRad) * std::cos(yawRad),
		std::cos(rollRad) * std::sin(yawRad) + std::sin(rollRad) * std::sin(pitchRad) * std::cos(yawRad)
	);
}
