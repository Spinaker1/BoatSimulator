#ifndef skybox_h
#define skybox_h

#include <vector>
#include "shprogram.h"

using namespace std;

extern glm::mat4 projection;
extern glm::mat4 view;
extern GLfloat brightness;

static GLuint skyboxTexture;

void createSkybox(GLuint & VBO, GLuint & EBO, GLuint & VAO);

void updateSkybox(ShaderProgram theProgram, GLuint & VAO, GLuint & EBO);

#endif
