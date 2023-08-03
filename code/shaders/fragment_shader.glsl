#version 330 core

layout (location = 0) out vec4 color;

in vec4 FragPosGeo;
in vec3 normal;

uniform int lightsCount;
uniform float lightSources[300];
uniform vec3 cameraPos;

void main()
{
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

        if (specularHighlight < 0.0 || diffusedLighting <= 0)
        {
            specularHighlight = 0.0;
        }
    }

    vec4 baseColor = vec4(0.5, 0.5, 0.5, 1.0);
    color = baseColor*diffusedLighting + specularHighlight;
    color.w = 1.0;
}