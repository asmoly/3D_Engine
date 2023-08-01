#pragma once

#include <iostream>

class Mesh
{
public:
    Mesh() = default;

    void load_from_obj(const char* pathToFile);

public:
    float* vertices;
    int vertexCount;
    unsigned int* indices;
    int indexCount;
};