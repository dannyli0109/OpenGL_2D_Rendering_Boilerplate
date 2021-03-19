#pragma once
#include <string>
#include <vector>
#include "GUI.h"
#include <sstream>
class Console
{
public:
	static Console* CreateInstance(int maxSize);
	static Console* GetInstance();
	void DrawGUI();
	static void Destroy();
	Console& operator<< (std::string message);
	Console& operator<< (const char* message);
	Console& operator<< (float message);
	Console& operator<< (double message);
	Console& operator<< (int message);
	Console& operator<< (bool flush);
	void Flush();
	
private:
	struct Message {
		std::string data = "";
		bool active = false;
	};
	Console(int maxSize) { 
		logs.resize(maxSize);
	};
	~Console() {};
	static Console* instance;
	std::vector<Message> logs;
	int index = 0;
	int startIndex = 0;
	std::string buffer = "";
};

