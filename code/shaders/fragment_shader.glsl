#version 330 core

layout (location = 0) out vec4 color;

in vec4 FragPosGeo;
in vec3 normal;

uniform int lightsCount;
uniform float lightSources[300];

void main()
{
    vec3 cameraPos = vec3(0.0, 0.0, 0.0);

    float diffusedLighting = 0.0;
    float specularHighlight = 0.0;
    for (int i = 0; i < lightsCount; i += 3)
    {
        vec3 lightSourcePos = vec3(lightSources[i], lightSources[i + 1], lightSources[i + 2]);
        vec3 pixelPos = vec3(FragPosGeo.x, FragPosGeo.y, FragPosGeo.z);
        
        vec3 pixelToLightVec = normalize(lightSourcePos - pixelPos);
        vec3 pixelToCameraVec = normalize(cameraPos - pixelPos);

        diffusedLighting = dot(pixelToLightVec, normal);

        vec3 lightReflectionVec = -pixelToLightVec + 2.0*dot(normal, pixelToLightVec)*normal;
        specularHighlight = dot(pixelToCameraVec, lightReflectionVec)*0.5;
    }

    color = vec4(0.0*diffusedLighting + specularHighlight, 0.2*diffusedLighting + specularHighlight, 0.8*diffusedLighting + specularHighlight, 1.0);
}