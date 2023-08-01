#pragma once

#include <vector>
#include <GL/glew.h>

struct VertexBufferElement
{
    unsigned int count;
    unsigned int type;
    unsigned char normalized;
};

class VertexBufferLayout
{
public:
    VertexBufferLayout();

    void push(unsigned int count);
    
public:
    std::vector<VertexBufferElement> elements;
    unsigned int stride;
};