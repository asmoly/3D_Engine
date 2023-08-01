#version 330 core

layout (location = 0) in vec4 position;

out vec4 FragPos;

uniform mat4 projectionMatrix;

void main()
{
    gl_Position = projectionMatrix*position;
    FragPos = position;
}