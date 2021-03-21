#include "EventManager.h"
#include "ConcreteEvent.h"
#include "ProgramManager.h"
#include "Event.h"
EventManager* EventManager::CreateInstance(ProgramManager* programManager)
{
	if (!instance)
	{
		instance = new EventManager(programManager);
	}
	return instance;
}

EventManager* EventManager::GetInstance()
{
	return instance;
}

void EventManager::Destroy()
{
	if (instance)
	{
		delete instance;
		instance = nullptr;
	}
}

void EventManager::OnMousePressed(glm::vec2 mousePos, MouseKey key)
{
	onMousePressed->Notify(mousePos, key);
	programManager->OnEvent(onMousePressed);
}

void EventManager::OnMouseReleased(MouseKey key)
{
	onMouseReleased->Notify(key);
	programManager->OnEvent(onMouseReleased);
}

void EventManager::OnMouseMove(glm::vec2 mousePos)
{
	onMouseMove->Notify(mousePos);
	programManager->OnEvent(onMouseMove);
}

void EventManager::OnMouseScroll(glm::vec2 mouseOff)
{
	onMouseScroll->Notify(mouseOff);
	programManager->OnEvent(onMouseScroll);
}

EventManager::EventManager(ProgramManager* programManager) {
	this->programManager = programManager;
	onMousePressed = new ConcreteEvent<std::function<void(glm::vec2 mousePosition, MouseKey key)>, glm::vec2, MouseKey>();
	onMouseReleased = new ConcreteEvent<std::function<void(MouseKey key)>, MouseKey>();
	onMouseMove = new ConcreteEvent<std::function<void(glm::vec2 mousePosition)>, glm::vec2>();
	onMouseScroll = new ConcreteEvent<std::function<void(glm::vec2 mouseOffset)>, glm::vec2>();
}

EventManager::~EventManager()
{
	delete onMousePressed;
	delete onMouseReleased;
	delete onMouseMove;
	delete onMouseScroll;
}

EventManager* EventManager::instance = nullptr;

