#include "Vector3.h"
#include "cmath"

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
