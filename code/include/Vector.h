#pragma once

class Vector
{
public:
    Vector() = default;
    Vector(float x, float y, float z, float w);

    void print();

    Vector operator+ (const Vector& vectorToAdd);
    Vector operator* (const float& scalar);

public:
    float x;
    float y;
    float z;
    float w;
};