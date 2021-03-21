#include "ConsoleLayer.h"

void ConsoleLayer::OnUpdate(float deltaTime)
{
	Console::GetInstance()->DrawGUI();
}
