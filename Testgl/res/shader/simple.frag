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

struct SpotLight {
	PointLight pointLight;
    vec3 direction;

	float innerCone;
	float outerCone;
};

uniform Material material;
uniform PointLight pointLight;
uniform SunLight sunLight;
uniform SpotLight spotLight;
uniform sampler2D tex;
uniform vec3 viewPos;

in vec3 Normal;
in vec2 TexCoord;
in vec3 FragPos; 

out vec4 FragColor;

vec3 calcSunLight(SunLight light, vec3 normal, vec3 viewDir)
{
    vec3 lightDir = normalize(-light.direction);
    vec3 reflectDir = reflect(-lightDir, normal);

    vec3 ambient  = light.color * material.ambient;
    vec3 diffuse = light.color * material.diffuse * max(dot(normal, lightDir), 0.0);
    vec3 specular = light.color * material.specular * pow(max(dot(viewDir, reflectDir), 0.0), material.shine);
    
	return ambient + diffuse + specular;
}

vec3 calcPointLight(PointLight light, vec3 normal, vec3 viewDir)
{
    float lightDistance = length(light.position - FragPos);
	float attenuation = 1.0 / (light.constant + light.linear * lightDistance + light.quadratic * lightDistance * lightDistance);    

	vec3 ambient = material.ambient * light.color * attenuation;

	vec3 lightDir = normalize(light.position - FragPos);
	vec3 diffuse = max(dot(normal, lightDir), 0.0) * material.diffuse * light.color * attenuation;

	vec3 reflectDir = reflect(-lightDir, normal);
	vec3 specular = material.specular * pow(max(dot(viewDir, reflectDir), 0.0), material.shine) * light.color * attenuation;

	return ambient + specular + diffuse;
}

vec3 calcSpotLight(SpotLight light, vec3 normal, vec3 viewDir)
{
	vec3 lightDir = normalize(light.pointLight.position - FragPos);
	float theta = dot(lightDir, normalize(-light.direction));
	float epsilon = light.innerCone - light.outerCone;
	float intensity = clamp((theta - light.outerCone) / epsilon, 0.0, 1.0);
	
	return intensity * calcPointLight(light.pointLight, normal, viewDir);
}

void main()
{
	vec3 normal = normalize(Normal);
	vec3 viewDir = normalize(viewPos - FragPos);

	vec3 pointLighting = calcPointLight(pointLight, normal, viewDir);
	vec3 sunLighting = calcSunLight(sunLight, normal, viewDir);
	vec3 spotLighting = calcSpotLight(spotLight, normal, viewDir);

    FragColor = vec4(pointLighting + sunLighting + spotLighting, 1.0) * texture(tex, TexCoord);
	//FragColor = vec4( spotLighting, 1.0) * texture(tex, TexCoord);
}
