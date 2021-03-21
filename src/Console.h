#pragma once
#include <string>
#include <vector>
#include "GUI.h"
#include <sstream>
#include <iomanip>
#include <time.h>

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
	void AddTimeStamp()
	{
		if (buffer.size() == 0)
		{
			auto t = std::time(nullptr);
			tm ts;
			localtime_s(&ts, &t);
			buffer += "[";
			buffer += std::to_string(ts.tm_hour);
			buffer += ":";
			buffer += std::to_string(ts.tm_min);
			buffer += ":";
			buffer += std::to_string(ts.tm_sec);
			buffer += "] ";
		}
	}
	~Console() {};
	static Console* instance;
	std::vector<Message> logs;
	int index = 0;
	int startIndex = 0;
	std::string buffer = "";
};

