#include "Texture.h"

#include "GL/glew.h"
#define STB_IMAGE_IMPLEMENTATION
#include "external/STB_IMAGE/stb_image.h"

Texture::Texture(const std::string& pathToImage)
{
    this->filePath = pathToImage;
}

void Texture::load()
{
    stbi_set_flip_vertically_on_load(1);
    int width = 0, height = 0, bpp = 0;
    unsigned char* imageData = stbi_load(this->filePath.c_str(), &width, &height, &bpp, 3);

    if (!imageData)
    {
        std::cout << "Error loading texture " << this->filePath << std::endl;
    }

    glGenTextures(1, &this->id);
    glBindTexture(GL_TEXTURE_2D, this->id);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, imageData);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

    glBindTexture(GL_TEXTURE_2D, 0);
    stbi_image_free(imageData);
}

void Texture::bind(unsigned int textureUnit) const
{
    glActiveTexture(GL_TEXTURE0 + textureUnit);
    glBindTexture(GL_TEXTURE_2D, this->id);
}

void Texture::unbind() const
{
    glBindTexture(GL_TEXTURE_2D, 0);
}