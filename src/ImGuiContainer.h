#pragma once
#include "GUI.h"
#include "Window.h"
class ImGuiContainer
{
public:
	ImGuiContainer() = default;
	~ImGuiContainer();

	ImGuiContainer(const ImGuiContainer& other) = delete;
	ImGuiContainer& operator=(const ImGuiContainer& other) = delete;
	ImGuiContainer(const ImGuiContainer&& other) = delete;
	ImGuiContainer& operator=(const ImGuiContainer&& other) = delete;

	void Init(Window* window);
	void Destroy();

	void Begin();
	void End();
};

