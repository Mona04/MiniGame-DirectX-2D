#pragma once

void Log_Error(const char* text, ...);

#define LOG_ERROR(text, ...)	{ std::string callerName = __FUNCTION__; Log_Error((callerName + " : " text).c_str(), __VA_ARGS__); }
