#version 330 core
in vec3 vecColor;
in vec2 TexCoord;

out vec4 color;

uniform sampler2D Texture0;

void main()
{
	vec3 lightColor = vec3(1.0f, 1.0f, 0.5f);
	float ambientStrength = 0.1f;
    vec3 ambient = ambientStrength * lightColor;

    vec3 result = ambient * vecColor;
    color = vec4(result, 1.0f);
}
