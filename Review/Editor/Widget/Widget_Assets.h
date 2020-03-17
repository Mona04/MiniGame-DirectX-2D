#pragma once
#include "IWidget.h"

class Widget_Assets final : public IWidget
{
public:
	Widget_Assets(class Context* context);
	~Widget_Assets();

	Widget_Assets(const Widget_Assets&) = delete;
	Widget_Assets& operator=(const Widget_Assets&) = delete;

	void Render() override;
	
private:
	void ShowItem();
	void UpdateItem(const std::string& path);
	void ChangeCurDirectory(const std::string& path);

private:
	class ResourceManager* resourceManager;

	float itemSize;
	float itemSizeMin;
	float itemSizeMax;
	std::string currentPath;
	std::vector<Item> items;
};