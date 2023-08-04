#version 330

layout(triangles) in;
layout(triangle_strip, max_vertices=3) out;

in vec4 FragPos[];
in vec2 TextureCoord[];
in vec3 FragNormal[];

out vec4 FragPosGeo;
out vec2 TextureCoordGeo;
out vec3 FragNormalGeo;
out vec3 normal;

uniform vec3 cameraPos;

void main(void)
{
    for (int i = 0; i < 3; i++) {
        vec3 A = FragPos[i].xyz;
        vec3 B = FragPos[(i + 1) % 3].xyz;
        vec3 C = FragPos[(i + 2) % 3].xyz;

        FragPosGeo = FragPos[i];
        TextureCoordGeo = TextureCoord[i];
        FragNormalGeo = FragNormal[i];

        vec3 edge1 = B - A;
        vec3 edge2 = C - A;

        vec3 N = normalize(cross(edge1, edge2));

        vec3 vertexToCameraVec = cameraPos - A;
        if (dot(vertexToCameraVec, N) < 0)
        {
            return;
        }

        gl_Position = gl_in[i].gl_Position;
        normal = N;
        EmitVertex();
    }
    EndPrimitive();
}
