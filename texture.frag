#version 330 core
in vec2 TexCoord;

out vec4 color;

uniform sampler2D Texture0;
uniform float brightness;

void main()
{
	color = texture(Texture0, TexCoord)*vec4(vec3(1.0,1.0,1.0)*brightness,1.0);
}
