#include "Shader.h"

#include <fstream>
#include <string>
#include "GL/glew.h"

Shader::Shader(const std::string& vertexShaderPath, const std::string& geometryShaderPath, const std::string& fragmentShaderPath)
{
    std::string vertexShaderSource = Shader::read_shader_source(vertexShaderPath);
    std::string geometryShaderSource = Shader::read_shader_source(geometryShaderPath);
    std::string fragmentShaderSource = Shader::read_shader_source(fragmentShaderPath);

    this->id = create_shader(vertexShaderSource, geometryShaderSource, fragmentShaderSource);
}

std::string Shader::read_shader_source(const std::string& filePath)
{
    std::ifstream fileStream(filePath);
    if (!fileStream.is_open()) {
        std::cout << "Error failed to open shader file" << std::endl;
        return "";
    }

    std::string sourceCode;
    std::string line;
    while (getline(fileStream, line)) {
        sourceCode += line + "\n";
    }

    fileStream.close();
    return sourceCode;
}

unsigned int Shader::compile_shader(unsigned int type, const std::string& source)
{
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE)
    {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* errorMessage = (char*)alloca(length*sizeof(char));
        glGetShaderInfoLog(id, length, &length, errorMessage);
        
        std::cout << "Failed to compile" << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader!" << std::endl;
        std::cout << errorMessage << std::endl;

        glDeleteShader(id);
        return 0;
    }

    return id;
}

unsigned int Shader::create_shader(const std::string& vertexShaderSource, const std::string& geometryShaderSource, const std::string& fragmentShaderSource)
{
    unsigned int program = glCreateProgram();
    unsigned int vertexShader = compile_shader(GL_VERTEX_SHADER, vertexShaderSource);
    unsigned int geometryShader = compile_shader(GL_GEOMETRY_SHADER, geometryShaderSource);
    unsigned int fragmentShader = compile_shader(GL_FRAGMENT_SHADER, fragmentShaderSource);

    glAttachShader(program, vertexShader);
    glAttachShader(program, geometryShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vertexShader);
    glDeleteShader(geometryShader);
    glDeleteShader(fragmentShader);

    return program;
}

void Shader::bind() const
{
    glUseProgram(this->id);
}

void Shader::unbind() const
{
    glUseProgram(0);
}

void Shader::set_uniform_mat4(const Matrix& matrix, const std::string& name, const bool& transpose)
{
    if (transpose == false)
    {
        glUniformMatrix4fv(Shader::get_unfirom_location(name), 1, GL_FALSE, &matrix.data[0]);
    }
    else
    {
        glUniformMatrix4fv(Shader::get_unfirom_location(name), 1, GL_TRUE, &matrix.data[0]);
    }
}

void Shader::set_uniform_array(float* array, const int& arrayLength, const std::string& name)
{
    glUniform1fv(Shader::get_unfirom_location(name), arrayLength, &array[0]);
}

void Shader::set_uniform_int(const int& number, const std::string& name)
{
    glUniform1i(Shader::get_unfirom_location(name), number);
}

void Shader::set_uniform_vec3(const float& x, const float& y, const float& z, const std::string& name)
{
    glUniform3f(Shader::get_unfirom_location(name), x, y, z);
}

int Shader::get_unfirom_location(const std::string& name)
{
    if (this->uniformLocationCache.find(name) != this->uniformLocationCache.end())
    {
        return this->uniformLocationCache[name];
    }

    int location = glGetUniformLocation(this->id, name.c_str());
    if (location == -1)
    {
        std::cout << "Uniform " << name << " not found" << std::endl;
    }
    else
    {
        this->uniformLocationCache[name] = location;
    }

    return location;
}

Shader::~Shader()
{
    glDeleteProgram(this->id);
}