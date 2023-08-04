#pragma once

#include <iostream>

class Texture
{
public:
    Texture() = default;
    Texture(const std::string& pathToImage);

    void load();

    void bind(unsigned int textureUnit = 0) const;
    void unbind() const;

private:
    unsigned int id;
    std::string filePath;
};