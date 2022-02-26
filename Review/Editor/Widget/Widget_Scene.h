#pragma once
#include "IWidget.h"

class Widget_Scene final : public IWidget
{
public:
	Widget_Scene(class Context* context);
	~Widget_Scene();

	Widget_Scene(const Widget_Scene&) = delete;
	Widget_Scene& operator=(const Widget_Scene&) = delete;

	void Render() override;

private:
	void ShowFrame();
	void Manipulate();
	void Picking();
	void DragAndDropEven();
	void CameraFocus();

private:
	class Input* input;
	class Timer* timer;
	class Renderer* renderer;
	class SceneManager* sceneManager;
	
	ImVec2 framePos;
	ImVec2 frameSize;
};