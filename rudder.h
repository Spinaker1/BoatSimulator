#ifndef rudder_h
#define rudder_h

#include <iostream>
#include "shprogram.h"

extern glm::mat4 projection;
extern glm::mat4 view;
extern GLfloat brightness;

static GLuint rudderTexture;

void createRudder(GLuint & VBO, GLuint & EBO, GLuint & VAO);

void updateRudder(ShaderProgram theProgram, GLuint & VAO, GLuint & EBO);

#endif