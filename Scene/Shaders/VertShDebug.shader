#version 330 core
layout (location = 0) in vec3 position;
layout (location = 2) in vec3 normal;

out VS_OUT {
    vec3 normal;
} vs_out;

uniform mat4 projection_matrix, view_matrix;

void main()
{
    gl_Position = projection_matrix * view_matrix * vec4(position, 1.0f); 
    mat3 normalMatrix = mat3(transpose(inverse(view_matrix)));
    vs_out.normal = normalize(vec3(projection_matrix * vec4(normalMatrix * normal, 1.0)));
}