#version 330 core
in vec3 TexCoords;
out vec4 color;

uniform samplerCube skybox;
uniform float brightness;

void main()
{    
    color = texture(skybox, TexCoords)*vec4(vec3(1.0,1.0,1.0)*brightness,1.0);
}