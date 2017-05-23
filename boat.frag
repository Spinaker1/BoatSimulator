#version 330 core

out vec4 color;

uniform sampler2D Texture0;

void main()
{
	vec3 lightColor = vec3(1.0f, 1.0f, 0.5f);
	float ambientStrength = 0.1f;
    vec3 ambient = ambientStrength * lightColor;

    color = vec4(1.0,1.0,0.0, 1.0f);
}
