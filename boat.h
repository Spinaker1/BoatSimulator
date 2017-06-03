#ifndef boat_h
#define boat_h

#include "shprogram.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <SOIL.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

extern glm::mat4 projection;
extern glm::mat4 view;
extern GLfloat brightness;

void createBoat(GLuint & VBO, GLuint & EBO, GLuint & VAO);

void updateBoat(ShaderProgram theProgram, GLuint & VAO, GLuint & EBO);

#endif