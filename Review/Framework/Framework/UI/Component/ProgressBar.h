#pragma once
#include "IUIWidget.h"

class ProgressBar : public IUIWidget
{
private:
	friend UI;
	friend MonsterManager;

private:
	ProgressBar(class Context* context);
	~ProgressBar() = default;

	void Update();
	void LoadFromFile(const std::string& path) override;
	void SaveToFile(const std::string& path) override;

public:
	void Init_Default();

	void SetProgress(const int& numerator, const int& denominator);
	void SetGaugeScale(const Vector3& var) { _gaugeScale = var; }

private:
	Vector3 _gaugeScale = Vector3(0 ,0 ,0);
};