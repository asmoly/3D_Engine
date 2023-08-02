#include <iostream>
#include <math.h>

#include "Matrix.h"

Matrix::Matrix (float* matrixData)
{
    this->data = new float[16];
    for (int i = 0; i < 16; i++)
    {
        this->data[i] = matrixData[i];
    }
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

Matrix Matrix::operator* (const Matrix& matrix)
{
    float* outputMatrixData = new float[16];

    outputMatrixData[0] = this->data[0]*matrix.data[0] + this->data[1]*matrix.data[4] + this->data[2]*matrix.data[8] + this->data[3]*matrix.data[12];
    outputMatrixData[1] = this->data[0]*matrix.data[1] + this->data[1]*matrix.data[5] + this->data[2]*matrix.data[9] + this->data[3]*matrix.data[13];
    outputMatrixData[2] = this->data[0]*matrix.data[2] + this->data[1]*matrix.data[6] + this->data[2]*matrix.data[10] + this->data[3]*matrix.data[14];
    outputMatrixData[3] = this->data[0]*matrix.data[3] + this->data[1]*matrix.data[7] + this->data[2]*matrix.data[11] + this->data[3]*matrix.data[15];

    outputMatrixData[4] = this->data[4]*matrix.data[0] + this->data[5]*matrix.data[4] + this->data[6]*matrix.data[8] + this->data[7]*matrix.data[12];
    outputMatrixData[5] = this->data[4]*matrix.data[1] + this->data[5]*matrix.data[5] + this->data[6]*matrix.data[9] + this->data[7]*matrix.data[13];
    outputMatrixData[6] = this->data[4]*matrix.data[2] + this->data[5]*matrix.data[6] + this->data[6]*matrix.data[10] + this->data[7]*matrix.data[14];
    outputMatrixData[7] = this->data[4]*matrix.data[3] + this->data[5]*matrix.data[7] + this->data[6]*matrix.data[11] + this->data[7]*matrix.data[15];

    outputMatrixData[8] = this->data[8]*matrix.data[0] + this->data[9]*matrix.data[4] + this->data[10]*matrix.data[8] + this->data[11]*matrix.data[12];
    outputMatrixData[9] = this->data[8]*matrix.data[1] + this->data[9]*matrix.data[5] + this->data[10]*matrix.data[9] + this->data[11]*matrix.data[13];
    outputMatrixData[10] = this->data[8]*matrix.data[2] + this->data[9]*matrix.data[6] + this->data[10]*matrix.data[10] + this->data[11]*matrix.data[14];
    outputMatrixData[11] = this->data[8]*matrix.data[3] + this->data[9]*matrix.data[7] + this->data[10]*matrix.data[11] + this->data[11]*matrix.data[15];

    outputMatrixData[12] = this->data[12]*matrix.data[0] + this->data[13]*matrix.data[4] + this->data[14]*matrix.data[8] + this->data[15]*matrix.data[12];
    outputMatrixData[13] = this->data[12]*matrix.data[1] + this->data[13]*matrix.data[5] + this->data[14]*matrix.data[9] + this->data[15]*matrix.data[13];
    outputMatrixData[14] = this->data[12]*matrix.data[2] + this->data[13]*matrix.data[6] + this->data[14]*matrix.data[10] + this->data[15]*matrix.data[14];
    outputMatrixData[15] = this->data[12]*matrix.data[3] + this->data[13]*matrix.data[7] + this->data[14]*matrix.data[11] + this->data[15]*matrix.data[15];

    Matrix outputMatrix(outputMatrixData);
    delete(outputMatrixData);

    return outputMatrix;
}

Matrix Matrix::create_rotation_matrix(const float& xRotation, const float& yRotation, const float zRotation)
{
    float xRotationInRad = (xRotation*3.1415)/180.0;
    float yRotationInRad = (yRotation*3.1415)/180.0;
    float zRotationInRad = (zRotation*3.1415)/180.0;

    float xRotationMatrixData[16] = {1.0f, 0.0f, 0.0f, 0.0f,
                                     0.0f, cosf(xRotationInRad), -sinf(xRotationInRad), 0.0f,
                                     0.0f, sinf(xRotationInRad), cosf(xRotationInRad), 0.0f,
                                     0.0f, 0.0f, 0.0f, 1.0f};

    float yRotationMatrixData[16] = {cosf(yRotationInRad), 0.0f, sin(yRotationInRad), 0.0f,
                                     0.0f, 1.0f, 0.0f, 0.0f,
                                     -sinf(yRotationInRad), 0.0f, cosf(yRotationInRad), 0.0f,
                                     0.0f, 0.0f, 0.0f, 1.0f};

    float zRotationMatrixData[16] = {cosf(zRotationInRad), -sinf(zRotationInRad), 0.0f, 0.0f,
                                     sinf(zRotationInRad), cosf(zRotationInRad), 0.0f, 0.0f,
                                     0.0f, 0.0f, 1.0f, 0.0f,
                                     0.0f, 0.0f, 0.0f, 1.0f};

    Matrix xRotationMatrix(xRotationMatrixData);
    Matrix yRotationMatrix(yRotationMatrixData);
    Matrix zRotationMatrix(zRotationMatrixData);

    Matrix rotationMatrix = xRotationMatrix*yRotationMatrix*zRotationMatrix;
    return rotationMatrix;
}

Matrix Matrix::create_transform_matrix(const float& xRotation, const float& yRotation, const float zRotation, const float& xMovement, const float& yMovement, const float zMovement)
{
    Matrix transformMatrix = Matrix::create_rotation_matrix(xRotation, yRotation, zRotation);
    transformMatrix.data[3] = xMovement;
    transformMatrix.data[7] = yMovement;
    transformMatrix.data[11] = zMovement;

    return transformMatrix;
}