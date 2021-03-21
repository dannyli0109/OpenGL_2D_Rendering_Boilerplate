#include "Window.h"
#include "EventManager.h"
#include "Event.h"
Window* Window::CreateInstance()
{
	if (!instance)
	{
		instance = new Window();
	}
	return instance;
}

Window* Window::GetInstance()
{
	return instance;
}

Window::~Window()
{
	glfwTerminate();
}

bool Window::Init(int width, int height, std::string name)
{
	if (!glfwInit())
		return false;

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

	glfwSetWindowUserPointer(glfwWindow, this);

	glfwSetCursorPosCallback(glfwWindow, OnMouseMove);
	glfwSetScrollCallback(glfwWindow, OnMouseScroll);

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
	if (instance) delete instance;
	instance = nullptr;
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

void Window::OnMouseMove(GLFWwindow* window, double x, double y)
{
	EventManager::GetInstance()->OnMouseMove({ x, y });
}

void Window::OnMouseScroll(GLFWwindow* window, double xoff, double yoff)
{
	EventManager::GetInstance()->OnMouseScroll({ xoff, yoff });
}

Window* Window::instance = nullptr;

