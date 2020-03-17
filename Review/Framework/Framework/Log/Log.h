#pragma once

enum class LogType : uint
{
	Info,
	Warning,
	Error
};

#define LOG_INFO(text)				{Log::callerName = __FUNCTION__; Log::Write(text, LogType::Info); }
#define LOG_WARNING(text)			{Log::callerName = __FUNCTION__; Log::Write(text, LogType::Info); }
#define LOG_ERROR(text)				{Log::callerName = __FUNCTION__; Log::Write(text, LogType::Info); }
#define LOG_INFO_F(text, ...)		{Log::callerName = __FUNCTION__; Log::InfoF(text, __VA_ARGS__); }
#define LOG_WARNING_F(text, ...)	{Log::callerName = __FUNCTION__; Log::WarningF(text, __VA_ARGS__); }
#define LOG_ERROR_F(text, ...)		{Log::callerName = __FUNCTION__; Log::ErrorF(text, __VA_ARGS__); }


class Log final
{
public:
	static void SetLogger(class ILogger* ilogger) { iLogger = ilogger; }

	static void InfoF(const char* text, ...);
	static void WarningF(const char* text, ...);
	static void ErrorF(const char* text, ...);

	template <typename T, typename = typename std::enable_if <
		std::is_same<T, int>::value ||
		std::is_same<T, uint>::value ||
		std::is_same<T, long>::value ||
		std::is_same<T, unsigned long>::value ||
		std::is_same<T, long long>::value ||
		std::is_same<T, float>::value ||
		std::is_same<T, double>::value ||
		std::is_same<T, long double>::value
		>::type>
		static void Write(const T& value, const LogType& type) { Write(std::to_string(value).c_str(), type); }
	
	static void Write(const char* text, const LogType& type);
	static void Write(const bool& value, const LogType& type);

	static void LogToLogger(const char* text, const LogType& type);
	static void LogToFile(const char* text, const LogType& type);

public:
	static std::string callerName;

private:
	static class ILogger* iLogger;
	static std::string fileName;
	static std::mutex logMutex;
	static bool bFirstLog;
};