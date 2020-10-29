#pragma once
#include <string>
#define _LOGGER_H

class Logger
{
public:
	
	static Logger* Instance();
	static void Release();

	static bool Initialized();

	void Log(std::string text);

	void LogDebugText(std::string text);
private:

	static Logger* sInstance; //Pointer and is a singleton since we only need 1 instance
	static bool sInitialized; //Determines if the logger initialized correctly

	Logger();
	~Logger();
};