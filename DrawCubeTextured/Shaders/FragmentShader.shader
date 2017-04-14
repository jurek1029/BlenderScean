#version 450 core
uniform sampler2D texture1;
in vec2 texcoord;
out vec4 out_color;
 

void main(void)
{
	vec4 color = texture(texture1, texcoord);
	out_color = color;
}