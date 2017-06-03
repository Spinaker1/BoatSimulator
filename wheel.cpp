#include "wheel.h"

GLuint wheelIndices[] = {
	0, 1, 2,
	0, 2, 3,
};

GLfloat wheelVertices[] = {
	// coordinates			// color			// texture
	0.2f, 0.2f, -0.799, 1.0f, 0.0f,
	-0.2f, 0.2f, -0.799f, 1.0f, 1.0f,
	-0.2f, -0.2f, -0.799f, 0.0f, 1.0f,
	0.2f, -0.2f, -0.799f, 0.0f, 0.0f,
};

GLfloat wheelRotAngle = 0;

void createWheel(GLuint & VBO, GLuint & EBO, GLuint & VAO)
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	// Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(wheelVertices), wheelVertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(wheelIndices), wheelIndices, GL_STATIC_DRAW);

	// vertex geometry data
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	// vertex texture coordinates
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0); // Note that this is allowed, the call to glVertexAttribPointer registered VBO as the currently bound vertex buffer object so afterwards we can safely unbind

	glBindVertexArray(0); // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs)

	// Set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// Set texture wrapping to GL_REPEAT (usually basic wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// Set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// prepare textures
	wheelTexture = LoadMipmapTexture(GL_TEXTURE0, "wheel.png");

}

void updateWheel(ShaderProgram theProgram, GLuint & VAO, GLuint & EBO)
{
	theProgram.Use();

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, wheelTexture);
	glUniform1i(glGetUniformLocation(theProgram.get_programID(), "wheelTexture"), 0);


	glm::mat4 trans;
	trans = glm::rotate(trans, -(float)glm::radians(wheelRotAngle), glm::vec3(0.0, 0.0, 1.0));

	if (wheelRotAngle >= 500)
		wheelRotAngle = 500;
	if (wheelRotAngle <= -500)
		wheelRotAngle = -500;

	GLuint transformLoc = glGetUniformLocation(theProgram.get_programID(), "transform");
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));

	GLint projectionLoc = glGetUniformLocation(theProgram.get_programID(), "projection");
	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

	GLint viewLoc = glGetUniformLocation(theProgram.get_programID(), "view");
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

	GLint brightLoc = glGetUniformLocation(theProgram.get_programID(), "brightness");
	glUniform1f(brightLoc, brightness);
	// Draw our first triangl

	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, _countof(wheelIndices), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}