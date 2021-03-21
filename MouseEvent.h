#pragma once
#include "Event.h"
#include "Graphics.h"
class MouseEvent :
	public Event
{
public:
	virtual void Notify() override = 0;
protected:
	glm::vec2 mousePos = { 0, 0 };
};

