#include "stdafx.h"
#include "Core/Window.h"
#include "Core/Setting.h"
#include "Core/Engine.h"

void Initialize();

int APIENTRY WinMain
(
	HINSTANCE hInstance,
	HINSTANCE prevInstance,
	LPSTR lpszCmdParam,
	int nCmdShow
)
{
	Window::Create(hInstance, 360, 360);
	Window::Show();

	Initialize();

	Engine* engine = new Engine();
	engine->Initialize();
	Window::Command = std::bind(&Engine::Command, engine, std::placeholders::_1);
	Window::Paint = std::bind(&Engine::Paint, engine, std::placeholders::_1);
	Window::Typing = std::bind(&Engine::Typing, engine, std::placeholders::_1);

	while (Window::Update())
	{
		engine->Update();
	}
	
	Window::Destroy();

	SAFE_DELETE(engine);

	return 0;
}

void Initialize()
{
	Setting::Get()->SetHInstance(Window::hInstance);
	Setting::Get()->SetHWND(Window::hWnd);
	Setting::Get()->SetWidth(Window::GetWidth());
	Setting::Get()->SetHeight(Window::GetHeight());
}
