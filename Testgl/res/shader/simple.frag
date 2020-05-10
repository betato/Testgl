#version 330 core
struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shine;
}; 

uniform Material material;
uniform sampler2D tex;
uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 viewPos;

in vec3 Normal;
in vec2 TexCoord;
in vec3 FragPos; 

out vec4 FragColor;

void main()
{
	vec3 ambient = material.ambient * lightColor;

	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(lightPos - FragPos);
	vec3 diffuse = max(dot(norm, lightDir), 0.0) * material.diffuse * lightColor;

	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	vec3 specular = material.specular * pow(max(dot(viewDir, reflectDir), 0.0), material.shine) * lightColor;

    FragColor = vec4(ambient + diffuse + specular, 1.0) * texture(tex, TexCoord);
}
