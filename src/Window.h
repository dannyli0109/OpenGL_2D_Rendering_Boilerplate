#pragma once
#include <string>
#include "Graphics.h"

class Window
{
public:
	Window() = default;
	Window(const Window& other) = delete;
	Window& operator=(const Window& other) = delete;
	~Window();

	bool Init(int width, int height, std::string name);
	bool Running();
	void End();
	float GetTime();
	void Destroy();

	GLFWwindow* Get() { return glfwWindow; }
	glm::vec2 GetSize();
	bool ShouldUpdateSize();
private:
	GLFWwindow* glfwWindow;
	float width, height;
};

