#pragma once
#include "Graphics.h"
class Camera
{
public:
	Camera(glm::vec2 position, glm::vec2 windowSize, float zoom);

	glm::mat4 GetProjection();
	void SetWindowSize(glm::vec2 windowSize) { this->windowSize = windowSize; }
	void SetPosition(glm::vec2 position) { this->position = position; }
	float GetZoom() { return zoom; }
	void SetZoom(float zoom) { this->zoom = zoom; }
private:
	glm::vec2 position;
	float zoom;
	glm::vec2 windowSize;
};

