#pragma once
#include "GUI.h"
#include <string>
#include "Graphics.h"
#include "Camera.h"
#include "EventManager.h"
#include "ConcreteEvent.h"

class FrameBuffer;
class Window;

class SceneWindow
{
public:
	SceneWindow(std::string name, FrameBuffer* frameBuffer, Camera* camera);
	void Begin();
	bool ShouldUpdateSize();
	void Draw();
	void End();
	glm::vec2 GetWindowSize() { return { windowSize.x, windowSize.y }; }
	glm::vec2 GetWindowPos() { return { windowPos.x, windowPos.y }; }
	glm::vec2 GetCursorPos() { return cursorPos; }
	void SetCursorPos(glm::vec2 cursorPos) { this->cursorPos = cursorPos; }
private:
	std::string name;
	FrameBuffer* frameBuffer;
	Camera* camera;

	ImVec2 windowSize = { 0, 0 };
	ImVec2 windowPos = { 0, 0 };
	glm::vec2 cursorPos = { 0, 0 };
};

