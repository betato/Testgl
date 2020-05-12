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
uniform vec3 viewPos;

#define MAX_SUN_LIGHTS 4
#define MAX_POINT_LIGHTS 4
#define MAX_SPOT_LIGHTS 4
uniform int numSunLights;
uniform int numPointLights;
uniform int numSpotLights;
uniform SunLight sunLights[MAX_SUN_LIGHTS];
uniform PointLight pointLights[MAX_POINT_LIGHTS];
uniform SpotLight spotLights[MAX_SPOT_LIGHTS];

uniform sampler2D texDiffuse;
uniform sampler2D texSpecular;
//uniform sampler2D texNormal;
//uniform sampler2D texHeight;


in vec3 Normal;
in vec2 TexCoord;
in vec3 FragPos; 

out vec4 FragColor;

vec4 calcLight(vec3 normal, vec3 viewDir, vec3 lightDir, vec3 reflectDir)
{
	vec3 ambient = material.ambient;
	vec3 diffuse = max(dot(normal, lightDir), 0.0) * material.diffuse;
	vec3 specular = pow(max(dot(viewDir, reflectDir), 0.0), material.shine) * material.specular;

	return vec4(ambient + diffuse, 1.0) * texture(texDiffuse, TexCoord) + vec4(specular, 1.0) * texture(texSpecular, TexCoord);
}

vec4 calcSunLight(SunLight light, vec3 normal, vec3 viewDir)
{
    vec3 lightDir = normalize(-light.direction);
    vec3 reflectDir = reflect(-lightDir, normal);
	
	return calcLight(normal, viewDir, lightDir, reflectDir) * vec4(light.color, 1.0);
}

vec4 calcPointLight(PointLight light, vec3 normal, vec3 viewDir)
{
	float lightDistance = length(light.position - FragPos);
	float attenuation = 1.0 / (light.constant + light.linear * lightDistance + light.quadratic * lightDistance * lightDistance);    
	vec3 lightDir = normalize(light.position - FragPos);
	vec3 reflectDir = reflect(-lightDir, normal);

	return calcLight(normal, viewDir, lightDir, reflectDir) * attenuation * vec4(light.color, 1.0);
}

vec4 calcSpotLight(SpotLight light, vec3 normal, vec3 viewDir)
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

	FragColor = vec4(0.0);
	for(int i = 0; i < numPointLights; i++)
		FragColor += calcPointLight(pointLights[i], normal, viewDir);
	for(int i = 0; i < numSunLights; i++)
		FragColor += calcSunLight(sunLights[i], normal, viewDir);
	for(int i = 0; i < numSpotLights; i++)
		FragColor += calcSpotLight(spotLights[i], normal, viewDir);
}
