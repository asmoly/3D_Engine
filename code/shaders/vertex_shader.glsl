#version 330 core

layout (location = 0) in vec4 position;

out vec4 FragPos;

uniform mat4 projectionMatrix;
uniform mat4 modelTransform;
uniform mat4 cameraTransform;

void main()
{
    gl_Position = projectionMatrix*cameraTransform*modelTransform*position;
    FragPos = modelTransform*position;
}