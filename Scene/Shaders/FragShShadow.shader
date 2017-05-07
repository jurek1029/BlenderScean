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

in VS_OUT {
    vec3 FragPos;
    vec3 Normal;
    vec2 TexCoords;
    vec4 FragPosLightSpace;
} fs_in;
  
uniform vec3 viewPos;
uniform Material material;
uniform Light light;
uniform sampler2D texture1;
uniform sampler2D shadowMap;

out vec4 out_color;
 
 float ShadowCalculation(vec4 fragPosLightSpace, vec3 lightDir)
{
    vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
    projCoords = projCoords * 0.5 + 0.5;
	float currentDepth = projCoords.z;
	float bias = max(0.05 * (1.0 - dot(fs_in.Normal, lightDir)), 0.005); 
    float shadow = 0.0;
	vec2 texelSize = 1.0 / textureSize(shadowMap, 0);
	for(int x = -1; x <= 1; ++x)
	{
		for(int y = -1; y <= 1; ++y)
		{
			float pcfDepth = texture(shadowMap, projCoords.xy + vec2(x, y) * texelSize).r; 
			shadow += currentDepth - bias > pcfDepth ? 1.0 : 0.0;        
		}    
	}
	shadow /= 9.0;
	
	if(projCoords.z > 1.0)
        shadow = 0.0;
    return shadow;
}

void main(void)
{
	// ambient
    vec3 ambient = light.ambient * material.ambient;
  	
    // diffuse 
    vec3 norm = normalize(fs_in.Normal);
    vec3 lightDir = normalize(light.position - fs_in.FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * (diff * material.diffuse);
    
    // specular
    vec3 viewDir = normalize(viewPos - fs_in.FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specular * (spec * material.specular);  
        
	//vec3 result = ambient + diffuse + specular;
	vec3 color = texture(texture1, fs_in.TexCoords).rgb;
	float shadow = ShadowCalculation(fs_in.FragPosLightSpace, lightDir);
	vec3 lighting = (ambient + (1.0 - shadow) * (diffuse)) * color;
	//out_color = vec4(result,1.0f) * color;
	out_color = vec4(lighting, 1.0f);
	float gamma = 2.2;
    out_color.rgb = pow(out_color.rgb, vec3(1.0/gamma));
}


