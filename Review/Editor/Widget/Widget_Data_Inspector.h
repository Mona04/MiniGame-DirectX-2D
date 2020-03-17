#pragma once
#include "IWidget.h"

class Widget_Data_Inspector final : public IWidget
{
public:
	Widget_Data_Inspector(class Context* context);
	~Widget_Data_Inspector() = default;

	Widget_Data_Inspector(const Widget_Data_Inspector&) = delete;
	Widget_Data_Inspector& operator=(const Widget_Data_Inspector&) = delete;

	void Render() override;

private:
	void SelectDataType();
	void SelectData();
	void ShowData();

private:
	DataManager* dataManager;
	DataType currentDataType = DataType::Mob;
	IData* currentData = nullptr;
	std::vector<std::string> stringsForDataType;

};