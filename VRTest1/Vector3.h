#pragma once
struct Vector3
{
	float x, y, z;
	Vector3 getNormalized();
	Vector3(float x, float y, float z);
	Vector3 operator-(const Vector3& other);

	Vector3 cross(const Vector3& other);

	float dot(const Vector3& other);

	Vector3 operator*(float scalar);

	Vector3 operator+(const Vector3& other);
	Vector3 normalize();
};

