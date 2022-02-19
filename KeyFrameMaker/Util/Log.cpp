#include "stdafx.h"
#include "Log.h"

void Log_Error(const char* text, ...)
{
	char buffer[1024];
	va_list args;
	va_start(args, text);
	vsnprintf(buffer, sizeof(buffer), text, args);
	va_end(args);

	if (Setting::Get()->GetHWND() != 0)
		MessageBoxA(Setting::Get()->GetHWND(), buffer, nullptr, MB_OK);
}