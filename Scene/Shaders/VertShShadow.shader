#version 330 core
layout(location = 0) in vec3 in_position;
layout(location = 1) in vec2 in_texture;
layout(location = 2) in vec3 in_normal;

out VS_OUT {
    vec3 FragPos;
    vec3 Normal;
    vec2 TexCoords;
    vec4 FragPosLightSpace;
} vs_out;

uniform mat4 projection_matrix, view_matrix;
uniform mat4 lightSpaceMatrix;

void main()
{
	vs_out.TexCoords = in_texture;
	vs_out.FragPos = in_position;
    vs_out.Normal = in_normal; 
	vs_out.FragPosLightSpace = lightSpaceMatrix * vec4(vs_out.FragPos, 1.0);
	gl_Position = projection_matrix * view_matrix * vec4(in_position, 1);

}