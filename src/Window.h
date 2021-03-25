#pragma once
#include <string>
#include <functional>
#include "Matrices.h"

class GLFWwindow;

class Window
{
public:
	Window(int width, int height, std::string title);
	~Window();

	Window(const Window& other) = delete;
	Window& operator=(const Window& other) = delete;

	void Destroy();

	bool Init(int width, int height, std::string title);
	bool Running();
	void Update();
	float GetTime();

	GLFWwindow* Get() { return glfwWindow; }
	glm::vec2 GetSize();
	bool ShouldUpdateSize();

private:
	GLFWwindow* glfwWindow;
	float width, height;
};