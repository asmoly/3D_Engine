#pragma once

#include "Matrix.h"
#include "Vector.h"

class Camera
{
public:
    Camera();

    Matrix get_camera_transformation();
    Vector get_camera_direction();

public:
    float x, y, z;
    float xRotation, yRotation, zRotation;
};