#pragma once
#include "Graphics.h"
class Camera
{
public:
	Camera(glm::vec2 position, float zoom, glm::vec2 windowSize);
	glm::mat4 GetProjection();
	void SetWindowSize(glm::vec2 windowSize) { this->windowSize = windowSize; }
private:
	glm::vec2 position;
	float zoom;
	glm::vec2 windowSize;
};

