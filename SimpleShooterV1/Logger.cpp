#include "Logger.h"
#include <iostream>

Logger* Logger::sInstance = nullptr;
bool Logger::sInitialized = false;

Logger* Logger::Instance()
{
	if (sInstance == nullptr)
	{
		sInstance = new Logger();
	}
	return sInstance;
}

void Logger::Release()
{
	delete sInstance;
	sInstance = nullptr;

	sInitialized = false;
}

bool Logger::Initialized()
{
	return sInitialized;
}

void Logger::Log(std::string text)
{
	if (text.empty())
	{
		printf("\n*************************************\nNO TEXT\n**************************\n");

	}
	else
	{
		printf("\n*************************************\n%s\n**************************\n", text.c_str());
	}

	//std::cout << "Test";
}

void Logger::LogDebugText(std::string text)
{
	//printf("\n*************************************\n%s\n**************************\n", text.c_str());
}

Logger::Logger()
{

}

Logger::~Logger()
{

}

