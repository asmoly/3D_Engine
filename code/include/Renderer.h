#pragma once

#include <iostream>
#include <GL/glew.h>

#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "Mesh.h"

class Renderer
{
public:
    Renderer() = default;

    void clear() const;
    void draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader, const int& drawType);

private:

};