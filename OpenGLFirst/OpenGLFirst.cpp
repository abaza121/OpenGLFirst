// OpenGLFirst.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <cmath>

const GLint WIDTH = 800, HEIGHT = 600;
const float TORADIANS = 3.14f / 180.0f;

GLuint VAO, VBO, shader, uniformModel;

bool direction = true;
float triOffset = 0;
float triMaxOffset = 1;
float triIncrement = 0.005f;
float curAngle = 0.0f;

bool sizeDirection = true;
float curSize = 0.4f;
float maxSize = 0.8f;
float minSize = 0.1f;

// Vertex Shader
static const char* vShader = " \n\ #version 330 \n\ layout (location = 0) in vec3 pos; \n\ uniform mat4 uniformModel; \n\ void main(){ \n\ gl_Position = uniformModel * vec4(pos, 1.0); \n\}";
static const char* fShader = " \n\ #version 330 \n\ out vec4 color; \n\ void main(){ \n\ color = vec4(1.0f, 0.1f, 0.4f, 0.3f); \n\}";
void CreateTriangle()
{
	GLfloat vertices[] = {
		-1.0f, -1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,
		0.0f, 1.0f, 0.0f
	};

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

		glGenBuffers(1, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
			glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
			glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void AddShader(GLuint theProgram, const char* shaderCode, GLenum shaderType)
{
	GLuint theShader = glCreateShader(shaderType);
	const GLchar* theCode[1];
	theCode[0] = shaderCode;

	GLint codeLength[1];
	codeLength[0] = strlen(shaderCode);

	glShaderSource(theShader, 1, theCode, codeLength);
	glCompileShader(theShader);


	GLint result = 0;
	GLchar eLog[1024] = { 0 };

	glGetShaderiv(theShader, GL_COMPILE_STATUS, &result);

	if (!result)
	{
		glGetShaderInfoLog(shader, sizeof(eLog), NULL, eLog);
		printf("Error compiling the %d shader: '%s' \n",shaderType, eLog);
		return;
	}

	glAttachShader(theProgram, theShader);
}

void CompileShaders()
{
	shader = glCreateProgram();

	if (!shader) {
		printf("Error creating shader program!\n");
		return;
	}

	AddShader(shader, vShader, GL_VERTEX_SHADER);
	AddShader(shader, fShader, GL_FRAGMENT_SHADER);

	GLint result = 0;
	GLchar eLog[1024] = { 0 };

	glLinkProgram(shader);
	glGetProgramiv(shader, GL_LINK_STATUS, &result);

	if (!result)
	{
		glGetProgramInfoLog(shader, sizeof(eLog), NULL, eLog);
		printf("Error Linking program : '%s' \n", eLog);
		return;
	}

	glValidateProgram(shader);
	glGetProgramiv(shader, GL_VALIDATE_STATUS, &result);

	if (!result)
	{
		glGetProgramInfoLog(shader, sizeof(eLog), NULL, eLog);
		printf("Error Validating program : '%s' \n", eLog);
		return;
	}

	uniformModel = glGetUniformLocation(shader, "uniformModel");
	if (uniformModel == -1)
	{
		printf("Couldn't find model");
	}
}

int main()
{
    // Initialize GLFW
	if (!glfwInit())
	{
		printf("GLFW Initialization failed!");
		glfwTerminate();
		return 1;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	GLFWwindow *mainWindow = glfwCreateWindow(WIDTH, HEIGHT, "Test Window", NULL, NULL);
	if (!mainWindow)
	{
		printf("GLFW window creation failed!");
		glfwTerminate();
		return 1;
	}

	// Get Buffer size Information.
	int bufferWidth, bufferHeight;
	glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);

	// Set Context for GLEW to use
	glfwMakeContextCurrent(mainWindow);

	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK)
	{
		printf("GLEW init failed!");
		glfwDestroyWindow(mainWindow);
		glfwTerminate();
		return 1;
	}

	// Setup Viewport size
	glViewport(0,0, bufferWidth, bufferHeight);
	CreateTriangle();
	CompileShaders();

	// LOOP unity window closed
	while (!glfwWindowShouldClose(mainWindow))
	{
		// Get + Handle user input events
		glfwPollEvents();

		if (direction)
		{
			triOffset += triIncrement;
		}
		else
		{
			triOffset -= triIncrement;
		}

		if (abs(triOffset) >= triMaxOffset)
		{
			direction = !direction;
		}

		curAngle += 1;
		if (curAngle >= 360)
		{
			curAngle -= 360;
		}

		if (direction)
		{
			curSize += 0.001f;
		}
		else
		{
			curSize -= 0.001f;
		}

		if (curSize >= maxSize || curSize <= minSize)
		{
			sizeDirection = !sizeDirection;
		}

		// Clear window
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

			glUseProgram(shader);

			glm::mat4 model = glm::mat4(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);
			model = glm::translate(model, glm::vec3(triOffset, 0.0f, 0.0f));
			model = glm::scale(model, glm::vec3(curSize, curSize, curSize));
			//model = glm::rotate(model, curAngle * TORADIANS, glm::vec3(0, 0, 1));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			glBindVertexArray(VAO);
					glDrawArrays(GL_TRIANGLES, 0, 3);

				glBindVertexArray(0);

			glUseProgram(0);
		glfwSwapBuffers(mainWindow);
	}

	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
