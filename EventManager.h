#pragma once
#include <vector>
#include <functional>
//#include "Event.h"
#include "Graphics.h"

template <typename Func, typename... Args>
class ConcreteEvent;
class ProgramManager;

enum class MouseKey
{
	Left,
	Right,
	Middle
};

class EventManager
{
public:
	static EventManager* CreateInstance(ProgramManager* programManager);
	static EventManager* GetInstance();
	static void Destroy();

	typedef ConcreteEvent<std::function<void(glm::vec2 mousePosition, MouseKey key)>, glm::vec2, MouseKey> MousePressedEvent;
	typedef ConcreteEvent<std::function<void(MouseKey key)>, MouseKey> MouseReleasedEvent;
	typedef ConcreteEvent<std::function<void(glm::vec2 mousePosition)>, glm::vec2> MouseMoveEvent;
	typedef ConcreteEvent<std::function<void(glm::vec2 mouseOffset)>, glm::vec2> MouseScrollEvent;

	MousePressedEvent* onMousePressed = nullptr;
	MouseReleasedEvent* onMouseReleased = nullptr;
	MouseMoveEvent* onMouseMove = nullptr;
	MouseScrollEvent* onMouseScroll = nullptr;

	void OnMousePressed(glm::vec2 mousePos, MouseKey key);
	void OnMouseReleased(MouseKey key);
	void OnMouseMove(glm::vec2 mousePos);
	void OnMouseScroll(glm::vec2 mouseOff);
private:

	static EventManager* instance;
	ProgramManager* programManager;
	EventManager(ProgramManager* programManager);
	~EventManager();
};

