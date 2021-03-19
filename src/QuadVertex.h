#pragma once
#include "Graphics.h"

struct QuadVertex
{
	glm::vec3 position;
	glm::vec4 color;
	glm::vec2 uv;
	float textureIndex;
};
