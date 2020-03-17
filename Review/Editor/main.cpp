#include "stdafx.h"
#include "Editor.h"
#include "ImGui/imgui_impl_win32.h"

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND, UINT, WPARAM, LPARAM);

void Initialize();

int APIENTRY WinMain
(
	HINSTANCE hInstance,
	HINSTANCE prevInstance,
	LPSTR lpszCmdParam,
	int nCmdShow
)
{
	Window::Create(hInstance, 1280, 720);
	Window::Show();

	Initialize();

	Editor* editor = new Editor();
	Window::EditorProc = ImGui_ImplWin32_WndProcHandler;
	//Window::InputProc =  // is  defined in widget_scene

	Window::ResizeProc = [&editor](const uint& width, const uint& height)
	{
		if (editor)
			editor->Resize(width, height);
	};
	
	while (Window::Update())
	{
		editor->Update();
		editor->Render();
	}

	SAFE_DELETE(editor);
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
