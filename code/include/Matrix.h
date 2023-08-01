#pragma once

#include "Vector.h"

class Matrix
{
public:
    Matrix() = default;
    Matrix(float* data);

    void print();

    Vector operator* (const Vector& vector);

    static Matrix create_projection_matrix(const float& fov, const float& aspect, const float& near, const float& far);

public:
    float* data;
};