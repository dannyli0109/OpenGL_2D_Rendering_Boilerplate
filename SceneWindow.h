#pragma once
#include "GUI.h"
#include <string>
#include "Graphics.h"
#include "Camera.h"

class FrameBuffer;
class Window;

class SceneWindow
{
public:
	SceneWindow(std::string name, FrameBuffer* frameBuffer, Camera* camera, Window* window);
	void Begin();
	bool ShouldUpdateSize();
	void Draw();
	void End();
	glm::vec2 GetSize() { return { width, height }; }
	glm::vec2 GetCursorPos();
private:
	std::string name;
	FrameBuffer* frameBuffer;
	Camera* camera;
	Window* window;

	int width = 0;
	int height = 0;

	ImVec2 windowSize = { 0, 0 };
};

