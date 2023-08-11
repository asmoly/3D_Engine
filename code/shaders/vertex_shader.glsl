#version 330 core

layout (location = 0) in vec4 position;
layout (location = 1) in vec2 textureCoord;
layout (location = 2) in vec3 normal;

out vec4 FragPos;
out vec2 TextureCoord;
out vec3 FragNormal;

uniform mat4 projectionMatrix;
uniform mat4 modelTransform;
uniform mat4 cameraTransform;

void main()
{
    gl_Position = projectionMatrix*cameraTransform*modelTransform*position;
    FragPos = modelTransform*position;

    TextureCoord = textureCoord;
    FragNormal = mat3(transpose(inverse(modelTransform)))*normal;
}