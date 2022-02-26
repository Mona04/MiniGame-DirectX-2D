#pragma once
#include "IWidget.h"

class Widget_UI_Inspector final : public IWidget
{
public:
	Widget_UI_Inspector(class Context* context);
	~Widget_UI_Inspector() = default;

	Widget_UI_Inspector(const Widget_UI_Inspector&) = delete;
	Widget_UI_Inspector& operator=(const Widget_UI_Inspector&) = delete;

	void Render() override;
	
private:
	void ShowUI(class UI* ui);
	void ShowTransform(class Transform* transform);
	void ShowRenderable(class Renderable* renderable);
	void ShowAnimator(Animator* animator, class UIWidgetFrame* frame);
	void ShowScripter(Scripter* scripter, class UIWidgetFrame* frame);
	void ShowExtra(class IUIWidget* component);

	void ShowMaterialInRenderable(class Material* material);
	void ShowRenderableTextureSlot(class Renderable* material, const class Texture* texture, const char* name, const TextureType& type);

private:
	std::vector<std::string> stringsForSamplerCombobox;
};