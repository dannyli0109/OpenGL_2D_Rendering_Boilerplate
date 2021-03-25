#include "Window.h"
#include "Graphics.h"
Window::Window(int width, int height, std::string title)
{
	Init(width, height, title);
}

Window::~Window()
{
	glfwTerminate();
}

bool Window::Init(int width, int height, std::string title)
{
	if (!glfwInit())
	{
		return false;
	}
	
	if (glfwWindow)
	{
		Destroy();
	}

	glfwWindow = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);

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

	glfwSetWindowUserPointer(glfwWindow, this);

	return true;
}

bool Window::Running()
{
	return !glfwWindowShouldClose(glfwWindow);
}

void Window::Update()
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
	glfwDestroyWindow(glfwWindow);
	glfwWindow = nullptr;
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

