#include <iostream>
#include <math.h>

#include "Matrix.h"

Matrix::Matrix (float* data)
{
    this->data = data;
}

void Matrix::print()
{
    for (int i = 0; i < 4; i++)
    {
        std::cout << "[" << this->data[i*4 + 0] << ", " << this->data[i*4 + 1] << ", " << this->data[i*4 + 2] << ", " << this->data[i*4 + 3] << "]\n" << std::endl;
    }
}

Matrix Matrix::create_projection_matrix(const float& fov, const float& aspect, const float& near, const float& far)
{
    float* projectionMatrix = new float[16];

    for (int i = 0; i < 16; i++)
    {
        projectionMatrix[i] = 0.0f;
    }

    projectionMatrix[0] = 1.0f/(aspect*tanf((fov*0.5f*3.1415)/180.0f));
    projectionMatrix[5] = 1.0f/tanf((fov*0.5f*3.1415)/180.0f);
    projectionMatrix[10] = -(far + near)/(far - near);
    projectionMatrix[11] = -1.0f;
    projectionMatrix[14] = -(far * near)/(far-near);

    return Matrix(projectionMatrix);
}

Vector Matrix::operator* (const Vector& vector)
{
    Vector vectorToReturn;
    vectorToReturn.x = data[0]*vector.x + data[1]*vector.y + data[2]*vector.z + data[3]*vector.w;
    vectorToReturn.y = data[4]*vector.x + data[5]*vector.y + data[6]*vector.z + data[7]*vector.w;
    vectorToReturn.z = data[8]*vector.x + data[9]*vector.y + data[10]*vector.z + data[11]*vector.w;
    vectorToReturn.w = data[12]*vector.x + data[13]*vector.y + data[14]*vector.z + data[15]*vector.w;
    return vectorToReturn;
}