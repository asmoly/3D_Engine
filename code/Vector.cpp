#include <iostream>

#include "Vector.h"

Vector::Vector(float x, float y, float z, float w)
{
    this->x = x;
    this->y = y;
    this->z = z;
    this->w = w;
}

void Vector::print()
{
    std::cout << "(" << this->x << ", " << this->y << ", " << this->z << ", " << this->w << ")" << std::endl;
}

Vector Vector::operator+ (const Vector& vectorToAdd)
{
    return Vector(this->x + vectorToAdd.x, this->y + vectorToAdd.y, this->z + vectorToAdd.z, this->w + vectorToAdd.w);
}

Vector Vector::operator* (const float& scalar)
{
    return Vector(this->x*scalar, this->y*scalar, this->z*scalar, this->w*scalar);
}