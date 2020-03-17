#include "Framework.h"
#include "Log.h"
#include "ILogger.h"

ILogger*		Log::iLogger;
std::string		Log::fileName;
std::string		Log::callerName;
std::mutex		Log::logMutex;
bool			Log::bFirstLog;

void Log::InfoF(const char * text, ...)
{
	char buffer[1024];
	va_list args;
	va_start(args, text);
	vsnprintf(buffer, sizeof(buffer), text, args);
	va_end(args);

	Write(buffer, LogType::Info);
}

void Log::WarningF(const char * text, ...)
{
	char buffer[1024];
	va_list args;
	va_start(args, text);
	vsnprintf(buffer, sizeof(buffer), text, args);
	va_end(args);

	Write(buffer, LogType::Warning);
}

void Log::ErrorF(const char * text, ...)
{
	char buffer[1024];
	va_list args;
	va_start(args, text);
	vsnprintf(buffer, sizeof(buffer), text, args);
	va_end(args);

	Write(buffer, LogType::Error);
}

void Log::Write(const char * text, const LogType & type)
{
	auto formatText = callerName.empty() ? std::string(text) : callerName + ":" + std::string(text);
	iLogger ? LogToLogger(formatText.c_str(), type) : LogToFile(formatText.c_str(), type);
}

void Log::Write(const bool & value, const LogType & type)
{
	value ? Write("True", type) : Write("False", type);
}

void Log::LogToLogger(const char * text, const LogType & type)
{
	std::lock_guard<std::mutex> guard(logMutex);
	iLogger->Log(std::string(text), static_cast<int>(type));
}

void Log::LogToFile(const char * text, const LogType & type)
{
	std::lock_guard<std::mutex> guard(logMutex);

	std::string prefix = 
		(type == LogType::Info) ? "Info : " :
		(type == LogType::Warning) ? "Warning : " : "Error : ";
	std::string finalText = prefix + text;

	std::ofstream out;
	out.open("log.txt", std::ios::out | std::ios::app);
	out << finalText.c_str() << std::endl;
	out.close();
}
