#ifndef boat_h
#define boat_h

#include "matrixes.h"
#include "shprogram.h"

GLfloat boatVertices[] = {
	// coordinates			// color			// texture
	0.4f, -0.2f, -1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f,
	-0.4f, -0.2f, -1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f,
	0.0f, -0.7f, -1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f,
	0.0f, -0.2f, -1.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
	0.4f, -0.2f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
	-0.4f, -0.2f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
	0.0f, -0.7f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,

	0.1f, -0.2f, -0.9f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
	-0.1f, -0.2f, -0.9f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
	-0.1f, 0.1f, -0.9f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
	0.1f, 0.1f, -0.9f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,

	0.1f, -0.2f, -0.8f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
	-0.1f, -0.2f, -0.8f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
	-0.1f, 0.1f, -0.8f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
	0.1f, 0.1f, -0.8f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
};

GLuint boatIndices[] = {
	0, 1, 2,
	0, 2, 3,
	0, 1, 3,
	1, 2, 3,
	0, 4, 5,
	0, 1, 5,
	0, 4, 6,
	0, 2, 6,
	1, 5, 6,
	1, 2, 6,
	4, 6, 5,

	7, 8, 9,
	7, 10, 9,

	11, 12, 13,
	11, 14, 13,

	8, 12, 13,
	8, 9, 13,

	9, 10, 13,
	14, 10, 13,

	7, 10, 11,
	7, 14, 11,
};


static GLfloat boatRotAngle = 0;
static GLfloat rotationFactor = 0;

void createBoat(GLuint & VBO, GLuint & EBO, GLuint & VAO)
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	// Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(boatVertices), boatVertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(boatIndices), boatIndices, GL_STATIC_DRAW);

	// vertex geometry data
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	// vertex color data
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0); // Note that this is allowed, the call to glVertexAttribPointer registered VBO as the currently bound vertex buffer object so afterwards we can safely unbind

	glBindVertexArray(0); // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs)
}

void updateBoat(ShaderProgram theProgram, GLuint & VAO, GLuint & EBO)
{
	theProgram.Use();

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glm::mat4 trans;
	trans = glm::rotate(trans, -glm::radians(boatRotAngle), glm::vec3(0.0, 1.0, 0.0));

	if (boatRotAngle >= 360.0f)
		boatRotAngle -= 360.0f;

	if (rotationFactor >= 1.0)
		rotationFactor = 1.0;
	if (rotationFactor <= -1.0)
		rotationFactor = -1.0;

	GLuint transformLoc = glGetUniformLocation(theProgram.get_programID(), "transform");
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));

	GLint projectionLoc = glGetUniformLocation(theProgram.get_programID(), "projection");
	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

	GLint viewLoc = glGetUniformLocation(theProgram.get_programID(), "view");
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, _countof(boatIndices), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}

#endif