#pragma once

#include "Vector.h"

class Matrix
{
public:
    Matrix() = default;
    Matrix(float* matrixData);

    void print();

    Vector operator* (const Vector& vector);
    Matrix operator* (const Matrix& matrix);

    static Matrix create_projection_matrix(const float& fov, const float& aspect, const float& near, const float& far);
    static Matrix create_rotation_matrix(const float& xRotation, const float& yRotation, const float zRotation);
    static Matrix create_transform_matrix(const float& xRotation, const float& yRotation, const float zRotation, const float& xMovement, const float& yMovement, const float zMovement);

public:
    float* data;
};