#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "FrameCounter.h"
#include "Camera.h"

class Window
{
public:
	Window(int width, int height);
	~Window();

	void init();
	void run();

private:
	inline static auto windowResizeCallback(GLFWwindow *wind, int width, int height) -> void
	{
		Window *window = static_cast<Window*>(glfwGetWindowUserPointer(wind));
		window->windowResized(width, height);
	}

	inline static auto mouseMoveCallback(GLFWwindow* wind, double xpos, double ypos) -> void
	{
		Window *window = static_cast<Window*>(glfwGetWindowUserPointer(wind));
		window->mouseMoved(xpos, ypos);
	}

	inline static auto mouseScrollCallback(GLFWwindow* wind, double xoffset, double yoffset) -> void
	{
		Window *window = static_cast<Window*>(glfwGetWindowUserPointer(wind));
		window->mouseScrolled(xoffset, yoffset);
	}

	void windowResized(int width, int height);
	void mouseMoved(double xpos, double ypos);
	void mouseScrolled(double xoffset, double yoffset);
	void processInput(GLFWwindow *window);

	GLFWwindow* window;
	FrameCounter frameCounter;
	Camera camera;

	int screenWidth;
	int screenHeight;
};
