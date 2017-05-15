#version 330 core
in vec3 Normal;
in vec3 Position;
out vec4 color;

uniform vec3 cameraPos;
uniform samplerCube skybox;

//vec3 ref(vec3 I, vec3 N)
//{
//	return I - 2.0 * dot(N, I) * N;
//}

void main()
{             
   vec3 I = normalize(Position - cameraPos);
   vec3 R = reflect(I, normalize(Normal));
   color = texture(skybox, R);
   //vec3 p = vec3(Position.x,Position.y - 5.51,Position.z);
   //color = texture(skybox, p);
}