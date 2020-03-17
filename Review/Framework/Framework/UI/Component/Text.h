#pragma once
#include "IUIComponent.h"

class Text final : public IUIComponent
{
private:
	friend UI;

private:
	Text(class Context* context);
	~Text();

	void Init() override;
	void Update() override;
	void LoadFromFile(const std::string& path) override {};
	void SaveToFile(const std::string& path) override {};

public:
	const std::wstring& GetText() { return text; }
	void SetText(const std::wstring& var);
	void SetTextFromMultibyte(const std::string& var);

private:
	ResourceManager* resourceManager;
	Glyphs glyphs;
	std::wstring text;
};