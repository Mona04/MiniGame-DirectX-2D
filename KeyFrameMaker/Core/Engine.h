#pragma once

class Engine
{
public:
	Engine();
	~Engine();

	void Initialize();
	void Update();

	void Create();	
	void Command(WPARAM wParam);
	void Typing(WPARAM wParam);
	void Paint(HDC hdc);

private:
	class Context* context;
	class ImageEditor* imageEditor;

	std::string input;

	HWND hWnd;
	HINSTANCE hInstance;
};