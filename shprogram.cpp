#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

#include <GL/glew.h>
#include "shprogram.h"

string read_shader_code(const GLchar* shaderPath)
{
	ifstream shader_file;
	shader_file.exceptions(ifstream::badbit);

	shader_file.open(shaderPath);
	stringstream shader_stream;
	shader_stream << shader_file.rdbuf();
	shader_file.close();
	return shader_stream.str();
}

GLuint compile_shader(const GLchar* shaderCode, GLenum shaderType)
{
	GLuint shader_id = glCreateShader(shaderType);
	glShaderSource(shader_id, 1, &shaderCode, NULL);
	glCompileShader(shader_id);

	// Print compile errors if any
	GLint success = 0;
	glGetShaderiv(shader_id, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		GLchar infoLog[512];
		glGetShaderInfoLog(shader_id, sizeof(infoLog), NULL, infoLog);
		string msg = string("Shader compilation: ") + infoLog;
		throw exception(msg.c_str());
	}
	return shader_id;
}

ShaderProgram::ShaderProgram(const GLchar* vertexPath, const GLchar* fragmentPath)
{
	// prepare vertex and fragment shaders
	string vertex_code = read_shader_code(vertexPath);
	GLuint vertex_id = compile_shader(vertex_code.c_str(), GL_VERTEX_SHADER);

	string fragment_code = read_shader_code(fragmentPath);
	GLuint fragment_id = compile_shader(fragment_code.c_str(), GL_FRAGMENT_SHADER);

	// link shader program
	program_id = glCreateProgram();
	glAttachShader(program_id, vertex_id);
	glAttachShader(program_id, fragment_id);
	glLinkProgram(program_id);

	// Print linking errors if any
	GLint success;
	glGetProgramiv(program_id, GL_LINK_STATUS, &success);
	if (!success)
	{
		GLchar infoLog[512];
		glGetProgramInfoLog(program_id, sizeof(infoLog), NULL, infoLog);
		string msg = string("Shader program linking: ") + infoLog;
		throw exception(msg.c_str());
	}

	// Delete the shaders as they're linked into our program now and no longer necessery
	glDeleteShader(vertex_id);
	glDeleteShader(fragment_id);
}

GLuint LoadMipmapTexture(GLuint texId, const char* fname)
{
	int width, height;
	unsigned char* image = SOIL_load_image(fname, &width, &height, 0, SOIL_LOAD_RGBA);

	GLuint texture;
	glGenTextures(1, &texture);

	glActiveTexture(texId);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);
	return texture;
}