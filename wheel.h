#ifndef wheel_h
#define wheel_h
#include "shprogram.h"

extern glm::mat4 projection;
extern glm::mat4 view;
extern GLfloat brightness;

static GLuint wheelTexture;

void createWheel(GLuint & VBO, GLuint & EBO, GLuint & VAO);
void updateWheel(ShaderProgram theProgram, GLuint & VAO, GLuint & EBO);

#endif
