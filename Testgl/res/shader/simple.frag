#version 330 core
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
	vec3 ambient = 0.1 * lightColor;

	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(lightPos - FragPos);
	vec3 diffuse = max(dot(norm, lightDir), 0.0) * lightColor;

	float specularStrength = 0.5;
	float shinyness = 2;
	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	vec3 specular = specularStrength * pow(max(dot(viewDir, reflectDir), 0.0), shinyness) * lightColor;

    FragColor = vec4(ambient + diffuse + specular, 1.0) * texture(tex, TexCoord);
}
