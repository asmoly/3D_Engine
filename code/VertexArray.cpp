#include "VertexArray.h"

#include "Renderer.h"

VertexArray::VertexArray()
{
    glGenVertexArrays(1, &this->id);
}

void VertexArray::bind() const
{
    glBindVertexArray(this->id);
}

void VertexArray::unbind() const
{
    glBindVertexArray(0);
}

void VertexArray::add_buffer(const VertexBuffer& vb, const VertexBufferLayout& layout)
{
    bind();
    vb.bind();
    const auto& elements = layout.elements;
    int64_t offset = 0;
    std::cout << elements.size() << std::endl;
    for (unsigned int i = 0; i < elements.size(); i++)
    {
        const auto& element = elements[i];
        glEnableVertexAttribArray(i);
        glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.stride, (const void*) offset);
        offset += element.count*sizeof(GL_FLOAT);
    }
}

VertexArray::~VertexArray()
{
    glDeleteVertexArrays(1, &this->id);
}