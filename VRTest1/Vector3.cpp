#include "Vector3.h"
#include "cmath"
#include <SDL_stdinc.h>

Vector3 Vector3::getNormalized()
{
    if (x == 0 && y == 0 && z == 0) {
        return Vector3(0, 0, 0);
    }
    float v = std::sqrt(x * x + y * y + z * z);
    return Vector3(x/v, y/v, z/v);
}

Vector3::Vector3(float x, float y, float z) : x(x), y(y), z(z)
{
}

Vector3 Vector3::operator-(const Vector3& other)
{
    return { x - other.x, y - other.y, z - other.z };
}
Vector3 Vector3::cross(const Vector3& other) {
    return {
        y * other.z - z * other.y,
        z * other.x - x * other.z,
        x * other.y - y * other.x
    };
}

float Vector3::dot(const Vector3& other) {
    return x * other.x + y * other.y + z * other.z;
}

Vector3 Vector3::operator*(float scalar) {
    return { x * scalar, y * scalar, z * scalar };
}

Vector3 Vector3::operator+(const Vector3& other) {
    return { x + other.x, y + other.y, z + other.z };
}

Vector3 Vector3::normalize()
{
    float magnitude = std::sqrt(x * x + y * y + z * z);
    return Vector3(
        x/magnitude,
        y/magnitude,
        z/magnitude
    );
}
