#ifndef rudder_h
#define rudder_h

#include "matrixes.h"
#include <iostream>

GLfloat rudderVertices[] = {
	// coordinates				// texture
	0.0f, -0.3f, 0.0f, 0.0f, 0.0f,
	0.0f, -0.3f, 0.2f, 1.0f, 0.0f,
	0.0f, -0.9f, 0.0f, 0.0f, 1.0f,
	0.0f, -0.9f, 0.2f, 1.0f, 1.0f,
};

GLuint rudderIndices[] = {
	0, 1, 3,
	0, 2, 3,
};

GLuint rudderTexture;

static GLfloat rudderRotAngle = 0;

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

void createRudder(GLuint & VBO, GLuint & EBO, GLuint & VAO)
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	// Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(rudderVertices), rudderVertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(rudderIndices), rudderIndices, GL_STATIC_DRAW);

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
	rudderTexture = LoadMipmapTexture(GL_TEXTURE0, "metal.png");

}

void updateRudder(ShaderProgram theProgram, GLuint & VAO, GLuint & EBO)
{
	theProgram.Use();

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, rudderTexture);
	glUniform1i(glGetUniformLocation(theProgram.get_programID(), "rudderTexture"), 0);


	glm::mat4 trans;
	trans = glm::rotate(trans, -(float)glm::radians(rudderRotAngle), glm::vec3(0.0, 1.0, 0.0));
	trans = glm::rotate(trans, -glm::radians(boatRotAngle), glm::vec3(0.0, 2.0, 0.0));

	if (rudderRotAngle >= 60)
		rudderRotAngle = 60;
	if (rudderRotAngle <= -60)
		rudderRotAngle = -60;

	GLuint transformLoc = glGetUniformLocation(theProgram.get_programID(), "transform");
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));

	GLint projectionLoc = glGetUniformLocation(theProgram.get_programID(), "projection");
	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

	GLint viewLoc = glGetUniformLocation(theProgram.get_programID(), "view");
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

	// Draw our first triangl

	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, _countof(rudderIndices), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

#endif