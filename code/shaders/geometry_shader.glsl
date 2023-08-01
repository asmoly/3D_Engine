#version 330

layout(triangles) in;
layout(triangle_strip, max_vertices=3) out;

in vec4 FragPos[];

out vec4 FragPosGeo;
out vec3 normal;

void main(void)
{
    for (int i = 0; i < 3; i++) {
        vec3 A = gl_in[i].gl_Position.xyz;
        vec3 B = gl_in[(i + 1) % 3].gl_Position.xyz;
        vec3 C = gl_in[(i + 2) % 3].gl_Position.xyz;

        FragPosGeo = FragPos[i];

        vec3 edge1 = B - A;
        vec3 edge2 = C - A;

        vec3 N = normalize(cross(edge1, edge2));

        gl_Position = gl_in[i].gl_Position;
        normal = N;
        EmitVertex();
    }
    EndPrimitive();
}
