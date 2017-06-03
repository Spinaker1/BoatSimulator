#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 aNormal;

out vec3 Normal;
out vec3 fragPos;

uniform mat4 projection; 
uniform mat4 view; 
uniform mat4 transform;
uniform vec3 lightPos; 

void main()
{
    gl_Position = projection * view * transform * vec4(position, 1.0f);
	Normal = aNormal;
	fragPos = vec3(transform * vec4(position, 1.0));
} 
