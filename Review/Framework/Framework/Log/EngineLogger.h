#pragma once
#include "Framework.h"
#include "ILogger.h"

struct LogPair
{
	std::string text;
	int type;
	LogPair(const std::string& text, const int& type) { this->text = text; this->type = type; }
};

class EngineLogger final : public ILogger
{
public:
	typedef std::function<void(const LogPair&)> LogFunction;

public:
	EngineLogger() = default;
	~EngineLogger() = default;

	EngineLogger(const EngineLogger&) = delete;
	EngineLogger& operator=(const EngineLogger&) = delete;

	void Log(const std::string& text, const int& type) override { func(LogPair(text, type)); }

	void SetCallBack(LogFunction&& func) { this->func = std::forward<LogFunction>(func); }

private:
	LogFunction func;
};