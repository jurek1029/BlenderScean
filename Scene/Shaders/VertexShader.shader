#version 330 core
layout(location = 0) in vec3 in_position;
layout(location = 1) in vec2 in_texture;
layout(location = 2) in vec3 in_normal;

uniform mat4 projection_matrix, view_matrix;

out vec2 texcoord;
out vec3 FragPos;
out vec3 Normal;

void main()
{
	texcoord = in_texture;
	FragPos = in_position;
    Normal = in_normal; 
	
	gl_Position = projection_matrix * view_matrix * vec4(in_position, 1);

}