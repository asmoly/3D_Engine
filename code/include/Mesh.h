#pragma once

#include <iostream>
#include "VertexArray.h"
#include "IndexBuffer.h"

class Mesh
{
public:
    Mesh(const char* pathToFile);

    void load_from_obj(const char* pathToFile);
    void create_buffers();
    void print();

public:
    float* vertices;
    unsigned int vertexCount;

    unsigned int* indices;
    unsigned int indexCount;

    int drawType;
};