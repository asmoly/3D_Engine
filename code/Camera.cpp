#include "Camera.h"

#include <math.h>

Camera::Camera()
{
    this->x = 0.0f;
    this->y = 0.0f;
    this->z = 0.0f;
    this->xRotation = 0.0f;
    this->yRotation = 0.0f;
    this->zRotation = 0.0f;
}

Matrix Camera::get_camera_transformation()
{
    Matrix centeringMat = Matrix::create_transform_matrix(0.0, 0.0, 0.0, -this->x, -this->y, -this->z);
    Matrix cameraTransform = Matrix::create_transform_matrix(-this->xRotation, -this->yRotation, -this->zRotation, -this->x, -this->y, -this->z);
    Matrix decenteringMat = Matrix::create_transform_matrix(0.0, 0.0, 0.0, this->x, this->y, this->z);

    return decenteringMat*cameraTransform*centeringMat;
}

Vector Camera::get_camera_direction()
{
    float xRotationInRad = (this->xRotation*3.1415)/180.0;
    float yRotationInRad = (this->yRotation*3.1415)/180.0;
    return Vector(sinf(yRotationInRad), -sinf(xRotationInRad), cosf(yRotationInRad), 0.0);
}