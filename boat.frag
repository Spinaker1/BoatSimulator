#version 330 core

out vec4 FragColor;

void main()
{
	vec3 objectColor = vec3(1.0f, 1.0f, 1.0f);
	vec3 lightColor = vec3(1.0f,1.0f,1.0f);

    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;

    vec3 result = ambient * objectColor;
    FragColor = vec4(result, 1.0f);
}  