#pragma once
#include "GUI.h"
//#include "Window.h"

class Window;
class ImGuiContainer
{
public:
	ImGuiContainer() = default;
	~ImGuiContainer();

	ImGuiContainer(const ImGuiContainer& other) = delete;
	ImGuiContainer& operator=(const ImGuiContainer& other) = delete;
	ImGuiContainer(const ImGuiContainer&& other) = delete;
	ImGuiContainer& operator=(const ImGuiContainer&& other) = delete;

	void Init();
	void Destroy();

	void Begin();
	void End();
};

