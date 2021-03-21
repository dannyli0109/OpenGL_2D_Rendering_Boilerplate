#pragma once
#include "Layer.h"
#include "Console.h"
class ConsoleLayer :
	public Layer
{
public:
	ConsoleLayer() = default;
	void OnUpdate(float deltaTime) override;
};

