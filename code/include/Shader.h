#pragma once

#include <iostream>
#include "unordered_map"

#include "Matrix.h"

class Shader
{
public:
    Shader() = default;
    Shader(const std::string& vertexShaderPath, const std::string& geometryShaderSource, const std::string& fragmentShaderPath);
    ~Shader();

    void bind() const;
    void unbind() const;

    void set_unfirom_mat4(const Matrix& matrix, const std::string& name);

private:
    unsigned int get_unfirom_location(const std::string& name);
    unsigned int compile_shader(unsigned int type, const std::string& source);
    unsigned int create_shader(const std::string& vertexShaderSource, const std::string& geometryShaderSource, const std::string& fragmentShaderSource);
    static std::string read_shader_source(const std::string& filePath);

private:
    unsigned int id;
    std::unordered_map<std::string, int> uniformLocationCache;
};