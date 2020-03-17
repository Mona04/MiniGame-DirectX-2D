#pragma once

class Editor final
{
public:
	Editor();
	~Editor();

	Editor(const Editor&) = delete;
	Editor* operator=(const Editor&) = delete;

	void Resize(const uint& width, const uint& height);
	void Update();
	void Render();

	const std::vector<class IWidget*>& GetWidgets() const { return widgets; }

private:
	void BeginDockspace();
	void EndDockspace();
	void ApplyStyle();

private:
	Context* context;
	class Engine* engine;
	Graphics* graphics;
	bool bUseDockspace;
	std::vector<class IWidget*> widgets;
};