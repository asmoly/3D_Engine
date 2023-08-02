#include "Renderer.h"

void Renderer::clear() const
{
    glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader, const int& drawType)
{
    shader.bind();
    va.bind();
    ib.bind();

    glDrawElements(drawType, ib.count, GL_UNSIGNED_INT, nullptr);
}