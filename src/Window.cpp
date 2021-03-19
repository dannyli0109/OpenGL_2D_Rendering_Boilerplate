#include "Window.h"

Window::~Window()
{
	glfwTerminate();
}

bool Window::Init(int width, int height, std::string name)
{
	if (!glfwInit())
		return false;

	// destroy existing window if exists
	Destroy();

	glfwWindow = glfwCreateWindow(width, height, name.c_str(), nullptr, nullptr);

	this->width = width;
	this->height = height;

	if (!glfwWindow)
	{
		glfwTerminate();
		return false;
	}

	glfwMakeContextCurrent(glfwWindow);

	if (!gladLoadGL())
		return false;

	glfwSetWindowPos(glfwWindow, 0, 30);

	glfwSwapInterval(1);

	return true;
}

bool Window::Running()
{
	return !glfwWindowShouldClose(glfwWindow);
}

void Window::End()
{
	glfwSwapBuffers(glfwWindow);
	glfwPollEvents();
}

float Window::GetTime()
{
	return glfwGetTime();
}

void Window::Destroy()
{
	if (glfwWindow) glfwDestroyWindow(glfwWindow);
}

glm::vec2 Window::GetSize()
{
	return glm::vec2(width, height);
}

bool Window::ShouldUpdateSize()
{
	int width, height;
	glfwGetWindowSize(glfwWindow, &width, &height);
	if (this->width == width && this->height == height) return false;
	this->width = width;
	this->height = height;
	return true;
}
