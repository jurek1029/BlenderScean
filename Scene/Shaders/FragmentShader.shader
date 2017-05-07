#version 330 core

struct Material 
{
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;    
    float shininess;
}; 

struct Light 
{
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

in vec3 FragPos;  
in vec3 Normal;
in vec2 texcoord;  
  
uniform vec3 viewPos;
uniform Material material;
uniform Light light;
uniform sampler2D texture1;

out vec4 out_color;
 

void main(void)
{
	// ambient
    vec3 ambient = light.ambient * material.ambient;
  	
    // diffuse 
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(light.position - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * (diff * material.diffuse);
    
    // specular
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specular * (spec * material.specular);  
        
	//vec3 result = ambient + diffuse + specular;
	vec3 result = ambient + diffuse;
	vec4 color = texture(texture1, texcoord);
	out_color = vec4(result,1.0f) * color;
	float gamma = 2.2;
    out_color.rgb = pow(out_color.rgb, vec3(1.0/gamma));
	//out_color = vec4(Normal, 1.0f);
}