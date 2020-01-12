#pragma once

#include <stdio.h>

#include <GL\glew.h>
#include <GLFW\glfw3.h>

class DrawWindow
{
public:
	DrawWindow();
	DrawWindow(GLint windowWidth, GLint windowHeight);
	int Initialize();

	GLfloat getBufferWidth() { return bufferWidth; }
	GLfloat getBufferHeight() { return bufferHeight; }

	bool getShouldClose() { return glfwWindowShouldClose(mainWindow); }

	void swapBuffers() { glfwSwapBuffers(mainWindow); }

	~DrawWindow();

private:
	GLFWwindow* mainWindow;
	GLint bufferWidth, bufferHeight, width, height;
};

