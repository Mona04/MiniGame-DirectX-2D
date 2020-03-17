#include "Framework.h"
#pragma comment(lib, "Framework.lib")

#include "Framework/core/Window.h"
#include "Framework/Core/Engine.h"

void Initialize();

int APIENTRY WinMain
(
	HINSTANCE hInstance, 
	HINSTANCE prevInstance, 
	LPSTR lpszCmdParam,
	int nCmdShow
)
{
	int width = 1080 + (GetSystemMetrics(SM_CXFRAME) << 1);
	int height = 720 + (GetSystemMetrics(SM_CYFRAME) << 1) + GetSystemMetrics(SM_CYCAPTION);

	Window::Create(hInstance, width, height);
	Window::Show();

	Initialize();

	Engine* engine = Engine::Get();
	engine->SetEngineFlags(
		EngineFlags::ENGINEFLAGS_RENDER | 
		EngineFlags::ENGINEFLAGS_UPDATE |
		EngineFlags::ENGINEFLAGS_GAME);

	Window::InputProc = std::bind(&Input::DefaultMouseProc, engine->GetContext()->GetSubsystem<Input>(),
		std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4);
	Window::ResizeProc = std::bind(&Engine::Resize, engine, std::placeholders::_1, std::placeholders::_2);

	while (Window::Update())
		engine->Update();

	Window::Destroy();

	return 0;
}

void Initialize()
{
	Setting::Get()->SetWindowInstance(Window::hInstance);
	Setting::Get()->SetWindowHandle(Window::Handle);
	Setting::Get()->SetWidth(Window::GetWidth());
	Setting::Get()->SetHeight(Window::GetHeight());
	Setting::Get()->SetIsVsync(false);
}