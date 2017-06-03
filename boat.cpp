#include "boat.h"

GLfloat boatVertices[] = {
	// coordinates			// normals		
	0.4f, -0.2f, -1.0f, 0.0f, 1.0f, 1.0f,
	-0.4f, -0.2f, -1.0f, 1.0f, 1.0f, 0.0f,
	0.0f, -0.7f, -1.0f, 1.0f, 0.0f, 1.0f,
	0.0f, -0.2f, -1.5f, 1.0f, 1.0f, 1.0f,
	0.4f, -0.2f, 0.0f, 0.0f, 0.0f, 1.0f,
	-0.4f, -0.2f, 0.0f, 0.0f, 0.0f, 1.0f,
	0.0f, -0.7f, 0.0f, 0.0f, 1.0f, 1.0f,

	//prost. przód
	0.1f, -0.2f, -0.9f, 0.0f, 0.0f, -1.0f,
	-0.1f, -0.2f, -0.9f, 0.0f, 0.0f, -1.0f,
	-0.1f, 0.1f, -0.9f, 0.0f, 0.0f, -1.0f,
	0.1f, 0.1f, -0.9f, 0.0f, 0.0f, -1.0f,

	//prost. ty³
	0.1f, -0.2f, -0.8f, 0.0f, 0.0f, 1.0f,
	-0.1f, -0.2f, -0.8f, 0.0f, 0.0f, 1.0f,
	-0.1f, 0.1f, -0.8f, 0.0f, 0.0f, 1.0f,
	0.1f, 0.1f, -0.8f, 0.0f, 0.0f, 1.0f,

	//rufa
	0.4f, -0.2f, 0.0f, 0.0f, 0.0f, 1.0f,
	-0.4f, -0.2f, 0.0f, 0.0f, 0.0f, 1.0f,
	0.0f, -0.7f, 0.0f, 0.0f, 0.0f, 1.0f,

	//pok³ad
	0.4f, -0.2f, -1.0f, 0.0f, 1.0f, 0.0f,
	-0.4f, -0.2f, -1.0f, 0.0f, 1.0f, 0.0f,
	0.0f, -0.2f, -1.5f, 0.0f, 1.0f, 0.0f,
	0.4f, -0.2f, 0.0f, 0.0f, 1.0f, 0.0f,
	-0.4f, -0.2f, 0.0f, 0.0f, 1.0f, 0.0f,

	//prost. prawo
	0.1f, -0.2f, -0.9f, 1.0f, 0.0f, 0.0f,
	0.1f, 0.1f, -0.9f, 1.0f, 0.0f, 0.0f,
	0.1f, -0.2f, -0.8f, 1.0f, 0.0f, 0.0f,
	0.1f, 0.1f, -0.8f, 1.0f, 0.0f, 0.0f,

	//prost. lewo
	-0.1f, -0.2f, -0.9f, 1.0f, 0.0f, 0.0f,
	-0.1f, 0.1f, -0.9f, 1.0f, 0.0f, 0.0f,
	-0.1f, -0.2f, -0.8f, 1.0f, 0.0f, 0.0f,
	-0.1f, 0.1f, -0.8f, 1.0f, 0.0f, 0.0f,

	//prost. góra
	-0.1f, 0.1f, -0.8f, 0.0f, 1.0f, 0.0f,
	0.1f, 0.1f, -0.8f, 0.0f, 1.0f, 0.0f,
	-0.1f, 0.1f, -0.9f, 0.0f, 1.0f, 0.0f,
	0.1f, 0.1f, -0.9f, 0.0f, 1.0f, 0.0f,

	//dziub prawy
	0.4f, -0.2f, -1.0f, 1.0f, -1.0f, -1.0f,
	0.0f, -0.7f, -1.0f, 1.0f, -1.0f, -1.0f,
	0.0f, -0.2f, -1.5f, 1.0f, -1.0f, -1.0f,

	//dziub lewy
	-0.4f, -0.2f, -1.0f, -1.0f, -1.0f, -1.0f,
	0.0f, -0.7f, -1.0f, -1.0f, -1.0f, -1.0f,
	0.0f, -0.2f, -1.5f, -1.0f, -1.0f, -1.0f,

	//prawa burta
	0.4f, -0.2f, -1.0f, 1.0f, -1.0f, 0.0f,
	0.4f, -0.2f, 0.0f, 1.0f, -1.0f, 0.0f,
	0.0f, -0.7f, 0.0f, 1.0f, -1.0f, 0.0f,
	0.0f, -0.7f, -1.0f, 1.0f, -1.0f, 0.0f,
	
	//lewa burta
	-0.4f, -0.2f, -1.0f, -1.0f, -1.0f, 0.0f,
	-0.4f, -0.2f, 0.0f, -1.0f, -1.0f, 0.0f,
	-0.0f, -0.7f, 0.0f, -1.0f, -1.0f, 0.0f,
	-0.0f, -0.7f, -1.0f, -1.0f, -1.0f, 0.0f,
};

GLuint boatIndices[] = {

	7, 8, 9,
	7, 10, 9,

	11, 12, 13,
	11, 14, 13,

	15, 16, 17,

	18, 21, 22,
	18, 19, 22,
	18, 19, 20,

	23, 24, 25,
	26, 25, 24,

	27, 28, 29,
	30, 29, 28,

	31, 32, 33,
	32, 34, 33,

	35, 37, 36,

	38, 40, 39,

	41, 42, 43,
	41, 44, 43,

	45, 46, 47,
	45, 48, 47,
};


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
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	// vertex color data
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0); // Note that this is allowed, the call to glVertexAttribPointer registered VBO as the currently bound vertex buffer object so afterwards we can safely unbind

	glBindVertexArray(0); // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs)
}

void updateBoat(ShaderProgram theProgram, GLuint & VAO, GLuint & EBO)
{
	theProgram.Use();

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glm::mat4 trans;
	trans = glm::rotate(trans, -glm::radians(0.0f), glm::vec3(0.0, 1.0, 0.0));

	GLuint transformLoc = glGetUniformLocation(theProgram.get_programID(), "transform");
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));

	GLint projectionLoc = glGetUniformLocation(theProgram.get_programID(), "projection");
	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

	GLint viewLoc = glGetUniformLocation(theProgram.get_programID(), "view");
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

	glm::vec3 lightPos = glm::vec3(1.5f, 1.0f, 1.5f);

	GLint lightLoc = glGetUniformLocation(theProgram.get_programID(), "lightPos");
	glUniform3fv(lightLoc, 1, glm::value_ptr(lightPos));

	GLint brightLoc = glGetUniformLocation(theProgram.get_programID(), "brightness");
	glUniform1f(brightLoc, brightness);

	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, _countof(boatIndices), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}
