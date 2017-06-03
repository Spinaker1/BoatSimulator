#version 330 core

out vec4 color;

uniform float brightness;

void main()
{
	color = vec4(vec3(0.50390625f, 0.60546875f, 0.75390625f)*brightness, 0.5f);
}
