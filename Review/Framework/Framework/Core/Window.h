#pragma once
#include "Framework.h"
#include "Framework/Core/Engine.h"

class Window final
{
public:	
	static inline LRESULT CALLBACK WndProc
	(
		HWND handle,
		uint message,
		WPARAM wParam,
		LPARAM lParam
	)
	{
		static bool isOn = true;
		if (isOn)
		{
			if (InputProc != nullptr)
				InputProc(handle, message, wParam, lParam);

			if (EditorProc != nullptr)
				EditorProc(handle, message, wParam, lParam);
		}

		switch (message)
		{
		case WM_CLOSE:
		case WM_DESTROY:
			PostQuitMessage(0);
			isOn = false;
			break;
		case WM_SIZE:
			if(ResizeProc) ResizeProc(GetWidth(), GetHeight());
			break;
		default:
			return DefWindowProc(handle, message, wParam, lParam);
		}

		return 0;
	}

	static inline void Create
	(
		HINSTANCE instance,
		const uint& width,
		const uint& height
	)
	{
		WNDCLASSEXW wndClass;
		wndClass.cbClsExtra = 0;
		wndClass.cbWndExtra = 0;
		wndClass.hbrBackground = static_cast<HBRUSH>(GetStockObject(WHITE_BRUSH));
		wndClass.hCursor = LoadCursor(nullptr, IDC_ARROW);
		wndClass.hIcon = LoadIcon(nullptr, IDI_ERROR);
		wndClass.hIconSm = LoadIcon(nullptr, IDI_ERROR);
		wndClass.hInstance = instance;
		wndClass.lpfnWndProc = static_cast<WNDPROC>(WndProc);
		wndClass.lpszClassName = L"D2DGame";
		wndClass.lpszMenuName = nullptr;
		wndClass.style = CS_HREDRAW | CS_VREDRAW;
		wndClass.cbSize = sizeof(WNDCLASSEX);

		WORD check = RegisterClassExW(&wndClass);
		assert(check != 0);

		Handle = CreateWindowExW
		(
			WS_EX_APPWINDOW,
			L"D2DGame",
			L"D2DGame",
			WS_OVERLAPPEDWINDOW,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			static_cast<int>(width),
			static_cast<int>(height),
			nullptr,
			nullptr,
			instance,
			nullptr
		);
		assert(Handle != nullptr);
	}

	static inline void Show()
	{
		SetForegroundWindow(Handle);
		SetFocus(Handle);
		ShowCursor(TRUE);
		ShowWindow(Handle, SW_SHOWNORMAL);
		UpdateWindow(Handle);
	}

	static inline const bool Update()
	{
		MSG msg;
		ZeroMemory(&msg, sizeof(MSG));

		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		return msg.message != WM_QUIT;
	}

	static inline void Destroy()
	{
		DestroyWindow(Handle);
		UnregisterClassW(L"D2DGame", hInstance);
	}

	static const uint GetWidth()
	{
		RECT rect;
		GetClientRect(Handle, &rect);
		return static_cast<uint>(rect.right - rect.left);
	}

	static const uint GetHeight()
	{
		RECT rect;
		GetClientRect(Handle, &rect);
		return static_cast<uint>(rect.bottom - rect.top);
	}

	public:
		static HINSTANCE hInstance;
		static HWND Handle;
		static std::function<LRESULT(HWND, uint, WPARAM, LPARAM)> InputProc;
		static std::function<LRESULT(HWND, uint, WPARAM, LPARAM)> EditorProc;
		static std::function<void(const uint&, const uint&)> ResizeProc;
};