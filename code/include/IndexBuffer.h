#pragma once

class IndexBuffer
{
public:
    IndexBuffer() = default;
    IndexBuffer(const unsigned int* data, unsigned int count);
    ~IndexBuffer();

    void bind() const;
    void unbind() const;

public:
    unsigned int count;

private:
    unsigned int id;
};