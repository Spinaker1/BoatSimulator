#ifndef water_h
#define water_h

#include <iostream>
#include "shprogram.h"

extern glm::mat4 projection;
extern glm::mat4 view;
extern GLfloat brightness;

void createWater(GLuint & VBO, GLuint & EBO, GLuint & VAO);

void updateWater(ShaderProgram theProgram, GLuint & VAO, GLuint & EBO);

#endif