#pragma once
#include "Graphics.h"
#include "EventManager.h"
#include "ConcreteEvent.h"
#include "Console.h"
class Camera
{
public:
	Camera(glm::vec2 position, float zoom, glm::vec2 windowSize);

	glm::mat4 GetProjection();
	void SetWindowSize(glm::vec2 windowSize) { this->windowSize = windowSize; }
	float GetZoom() { return zoom; }
	void SetZoom(float zoom) { this->zoom = zoom; }
private:
	glm::vec2 position;
	float zoom;
	glm::vec2 windowSize;
};

