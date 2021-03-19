#include "Console.h"

Console* Console::CreateInstance(int maxSize)
{
	if (!instance)
	{
		instance = new Console(maxSize);
	}
	return instance;
}

Console* Console::GetInstance()
{
	return instance;
}

void Console::DrawGUI()
{
	ImGui::Begin("Console");

	for (int i = 0; i < logs.size(); i++)
	{
		Message& log = logs[(i + startIndex) % logs.size()];
		if (!log.active) continue;
		ImGui::Text(log.data.c_str());
	}
	if (buffer.size() > 0)
	{
		ImGui::Text(buffer.c_str());
	}
	if (ImGui::GetScrollY() >= ImGui::GetScrollMaxY())
		ImGui::SetScrollHereY(1.0f);

	ImGui::End();
}
void Console::Destroy()
{
	if (instance) delete instance;
	instance = nullptr;
}

Console& Console::operator<<(std::string message)
{
	buffer += message;
	return *this;
}

Console& Console::operator<<(const char* message)
{
	buffer += message;
	return *this;
}

Console& Console::operator<<(float message)
{
	buffer += std::to_string(message);
	return *this;
}

Console& Console::operator<<(double message)
{
	buffer += std::to_string(message);
	return *this;
}

Console& Console::operator<<(int message)
{
	buffer += std::to_string(message);
	return *this;
}

Console& Console::operator<<(bool flush)
{
	if (flush)
	{
		Flush();
	}
	return *this;
}


void Console::Flush()
{
	if (buffer.size() == 0) return;
	Message& m = logs[index];
	m.active = true;
	m.data = buffer;
	if (index == startIndex)
	{
		startIndex = ++startIndex % logs.size();
	}
	index = ++index % logs.size();
	buffer.clear();
}
Console* Console::instance = nullptr;

