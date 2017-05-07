#version 330 core
layout (location = 0) in vec3 position;

uniform mat4 lightProjectionMatrix;
uniform mat4 lightViewMatrix;

void main()
{
    gl_Position = lightProjectionMatrix * lightViewMatrix * vec4(position, 1.0f);
}  