#include "Camera.h"

Camera::Camera(glm::vec2 position, glm::vec2 windowSize, float zoom)
{
	this->position = position;
	this->windowSize = windowSize;
	this->zoom = zoom;
}

glm::mat4 Camera::GetProjection()
{
	return glm::ortho(
		(-windowSize.x / 2.0f + position.x) / zoom, (windowSize.x / 2.0f + position.x) / zoom,
		(-windowSize.y / 2.0f + position.y) / zoom, (windowSize.y / 2.0f + position.y) / zoom, -1.0f, 1.0f
	);
}

