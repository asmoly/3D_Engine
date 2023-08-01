#version 330 core

layout (location = 0) out vec4 color;

in vec4 FragPosGeo;
in vec3 normal;

void main()
{
    //color = vec4(normal, 1.0);
    color = vec4(-FragPosGeo.z/10.0, 0.0, 0.0, 1.0);
}