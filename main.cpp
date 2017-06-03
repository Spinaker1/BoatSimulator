#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <SOIL.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "boat.h"
#include "rudder.h"
#include "shprogram.h"
#include "wheel.h"
#include "skybox.h"
#include "water.h"



using namespace std;

const GLuint WIDTH = 1000, HEIGHT = 600;
const float CAMERA_ROTATION = 2.0;
extern GLfloat rudderRotAngle;
extern GLfloat wheelRotAngle;
GLfloat brightness = 1.0;

glm::mat4 projection;
glm::mat4 view;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	if (key == GLFW_KEY_A)
	{
		wheelRotAngle -= 5.0;
		rudderRotAngle += 0.6f;
	}
	if (key == GLFW_KEY_D)
	{
		wheelRotAngle += 5.0;
		rudderRotAngle -= 0.6f;
	}
	if (key == GLFW_KEY_LEFT)
	{
		view = glm::translate(view, glm::vec3(0.0f, -0.0f, -0.5f));
		view = glm::rotate(view, glm::radians(CAMERA_ROTATION), glm::vec3(0.0, 1.0, 0.0));
		view = glm::translate(view, glm::vec3(0.0f, -0.0f, 0.5f));
	}
	if (key == GLFW_KEY_RIGHT)
	{
		view = glm::translate(view, glm::vec3(0.0f, -0.0f, -0.5f));
		view = glm::rotate(view, glm::radians(-CAMERA_ROTATION), glm::vec3(0.0, 1.0, 0.0));
		view = glm::translate(view, glm::vec3(0.0f, -0.0f, 0.5f));
	}
	if (key == GLFW_KEY_UP)
	{
		brightness += 0.01;
	}
	if (key == GLFW_KEY_DOWN)
	{
		brightness -= 0.01;
	}
}


ostream& operator<<(ostream& os, const glm::mat4& mx)
{
	for (int row = 0; row < 4; ++row)
	{
		for (int col = 0; col < 4; ++col)
			cout << mx[row][col] << ' ';
		cout << endl;
	}
	return os;
}

int main()
{
	projection = glm::perspective(45.0f, (float)WIDTH / (float)HEIGHT, 0.4f, 100.0f);
	view = glm::translate(view, glm::vec3(0.0f, -0.0f, -1.5f));
	view = glm::rotate(view, glm::radians((float)20.0), glm::vec3(1.0, 0.1, 0.0));

	if (glfwInit() != GL_TRUE)
	{
		cout << "GLFW initialization failed" << endl;
		return -1;
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	try
	{
		GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "GKOM - OpenGL 05", nullptr, nullptr);
		if (window == nullptr)
			throw exception("GLFW window not created");
		glfwMakeContextCurrent(window);
		glfwSetKeyCallback(window, key_callback);

		// Enable depth test
		glEnable(GL_DEPTH_TEST);
		// Accept fragment if it closer to the camera than the former one
		glDepthFunc(GL_LESS);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glewExperimental = GL_TRUE;
		if (glewInit() != GLEW_OK)
			throw exception("GLEW Initialization failed");

		glViewport(0, 0, WIDTH, HEIGHT);

		// Let's check what are maximum parameters counts
		GLint nrAttributes;
		glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
		cout << "Max vertex attributes allowed: " << nrAttributes << std::endl;
		glGetIntegerv(GL_MAX_TEXTURE_COORDS, &nrAttributes);
		cout << "Max texture coords allowed: " << nrAttributes << std::endl;

		ShaderProgram theProgram("boat.vert", "boat.frag");
		ShaderProgram theProgram2("texture.vert", "texture.frag");
		ShaderProgram theProgram3("skybox.vert", "skybox.frag");
		ShaderProgram theProgram4("water.vert", "water.frag");

		GLuint VBO, EBO, VAO;
		createBoat(VBO, EBO, VAO);

		GLuint VBO2, EBO2, VAO2;
		createRudder(VBO2, EBO2, VAO2);

		GLuint VBO3, EBO3, VAO3;
		createWheel(VBO3, EBO3, VAO3);

		GLuint VBO4, EBO4, VAO4;
		createSkybox(VBO4, EBO4, VAO4);

		GLuint VBO5, EBO5, VAO5;
		createWater(VBO5, EBO5, VAO5);

		// main event loop
		while (!glfwWindowShouldClose(window))
		{
			// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
			glfwPollEvents();

			// Clear the colorbuffer
			glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			updateSkybox(theProgram3, VAO4, EBO4);
			updateBoat(theProgram, VAO, EBO);
			updateRudder(theProgram2, VAO2, EBO2);
			updateWater(theProgram4, VAO5, EBO5);
			updateWheel(theProgram2, VAO3, EBO3);

			if (brightness >= 1.25) brightness = 1.25;
			if (brightness <= 0.5) brightness = 0.5;
			// Swap the screen buffers
			glfwSwapBuffers(window);
		}
		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);
		glDeleteBuffers(1, &EBO);
	}
	catch (exception ex)
	{
		cout << ex.what() << endl;
	}
	glfwTerminate();

	return 0;
}
