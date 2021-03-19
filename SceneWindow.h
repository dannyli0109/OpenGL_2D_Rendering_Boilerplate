#pragma once
#include "GUI.h"
#include <string>
#include "Graphics.h"
#include "Camera.h"

class FrameBuffer;

class SceneWindow
{
public:
	SceneWindow(std::string name, FrameBuffer* frameBuffer, Camera* camera);
	void Begin();
	bool ShouldUpdateSize();
	void Draw();
	void End();
	glm::vec2 GetSize() { return { width, height }; }
private:
	std::string name;
	FrameBuffer* frameBuffer;
	Camera* camera;

	int width = 0;
	int height = 0;
};

