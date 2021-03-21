#pragma once
#include <string>
#include "Graphics.h"
#include <functional>
//#include "EventManager.h"
//#include "Event.h"

class Window
{
public:
	static Window* CreateInstance();
	static Window* GetInstance();
	static void Destroy();

	Window(const Window& other) = delete;
	Window& operator=(const Window& other) = delete;


	bool Init(int width, int height, std::string name);
	bool Running();
	void End();
	float GetTime();

	GLFWwindow* Get() { return glfwWindow; }
	glm::vec2 GetSize();
	bool ShouldUpdateSize();

private:
	Window() = default;
	~Window();
	static void OnMouseMove(GLFWwindow* window, double x, double y);
	static void OnMouseScroll(GLFWwindow* window, double xoff, double yoff);
	GLFWwindow* glfwWindow;
	float width, height;
	static Window* instance;
};