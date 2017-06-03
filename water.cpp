#include "water.h"

GLfloat waterVertices[] = {
	// coordinates					
	3.0f, -0.4f, 3.0f,
	-3.0f, -0.4f, 3.0f,
	3.0f, -0.4f, -3.0f,
	-3.0f, -0.4f, -3.0f,
};

GLuint waterIndices[] = {
	0, 1, 2,
	3, 1, 2,
};

void createWater(GLuint & VBO, GLuint & EBO, GLuint & VAO)
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	// Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(waterVertices), waterVertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(waterIndices), waterIndices, GL_STATIC_DRAW);

	// vertex geometry data
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0); // Note that this is allowed, the call to glVertexAttribPointer registered VBO as the currently bound vertex buffer object so afterwards we can safely unbind

	glBindVertexArray(0); // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs)
}

void updateWater(ShaderProgram theProgram, GLuint & VAO, GLuint & EBO)
{
	theProgram.Use();

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glm::mat4 trans;

	trans = glm::rotate(trans, -(float)glm::radians(0.0f), glm::vec3(0.0, 1.0, 0.0));

	GLuint transformLoc = glGetUniformLocation(theProgram.get_programID(), "transform");
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));

	GLint projectionLoc = glGetUniformLocation(theProgram.get_programID(), "projection");
	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

	GLint viewLoc = glGetUniformLocation(theProgram.get_programID(), "view");
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

	GLint brightLoc = glGetUniformLocation(theProgram.get_programID(), "brightness");
	glUniform1f(brightLoc, brightness);

	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, _countof(waterIndices), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}