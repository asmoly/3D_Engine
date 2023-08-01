#include "VertexBufferLayout.h"

VertexBufferLayout::VertexBufferLayout()
{
    this->stride = 0;
}

void VertexBufferLayout::push(unsigned int count)
{
    VertexBufferElement vbe;
    vbe.count = count;
    vbe.type = GL_FLOAT;
    vbe.normalized = GL_FALSE;
    this->elements.push_back(vbe);
    this->stride += sizeof(GL_FLOAT)*count;
}