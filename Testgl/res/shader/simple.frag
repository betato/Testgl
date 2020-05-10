#version 330 core
struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shine;
};

struct PointLight {
    vec3 position;
    vec3 color;
	
    float constant;
    float linear;
    float quadratic;
};

struct SunLight {
    vec3 direction;
    vec3 color;
};

uniform Material material;
uniform PointLight pointLight;
uniform SunLight sunLight;
uniform sampler2D tex;
uniform vec3 viewPos;

in vec3 Normal;
in vec2 TexCoord;
in vec3 FragPos; 

out vec4 FragColor;

vec3 calcSunLight(vec3 normal, vec3 viewDir)
{
    vec3 lightDir = normalize(-sunLight.direction);
    vec3 reflectDir = reflect(-lightDir, normal);

    vec3 ambient  = sunLight.color * material.ambient;
    vec3 diffuse = sunLight.color * material.diffuse * max(dot(normal, lightDir), 0.0);
    vec3 specular = sunLight.color * material.specular * pow(max(dot(viewDir, reflectDir), 0.0), material.shine);
    
	return ambient + diffuse + specular;
}

vec3 calcPointLight(vec3 normal, vec3 viewDir)
{
    float lightDistance = length(pointLight.position - FragPos);
	float attenuation = 1.0 / (pointLight.constant + pointLight.linear * lightDistance + pointLight.quadratic * lightDistance * lightDistance);    

	vec3 ambient = material.ambient * pointLight.color * attenuation;

	vec3 lightDir = normalize(pointLight.position - FragPos);
	vec3 diffuse = max(dot(normal, lightDir), 0.0) * material.diffuse * pointLight.color * attenuation;

	vec3 reflectDir = reflect(-lightDir, normal);
	vec3 specular = material.specular * pow(max(dot(viewDir, reflectDir), 0.0), material.shine) * pointLight.color * attenuation;

	return ambient + specular + diffuse;
}

void main()
{
	vec3 normal = normalize(Normal);
	vec3 viewDir = normalize(viewPos - FragPos);

	vec3 pointLighting = calcPointLight(normal, viewDir);
	vec3 sunLighting = calcSunLight(normal, viewDir);

    FragColor = vec4(pointLighting + sunLighting, 1.0) * texture(tex, TexCoord);
}
