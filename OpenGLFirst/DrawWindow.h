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

	bool* getKeys() { return keys; }

	GLfloat getXChange();
	GLfloat getYChange();

	void swapBuffers() { glfwSwapBuffers(mainWindow); }

	~DrawWindow();

private:
	GLFWwindow* mainWindow;
	GLint bufferWidth, bufferHeight, width, height;

	bool keys[1024];

	GLfloat lastX;
	GLfloat lastY;
	GLfloat xChange = 0;
	GLfloat yChange = 0;

	bool mouseFirstMoved;

	void createCallbacks();
	static void handleKeys(GLFWwindow *window, int key, int code, int action, int mode);
	static void handleMouse(GLFWwindow* window, double xPos, double yPos);
};

