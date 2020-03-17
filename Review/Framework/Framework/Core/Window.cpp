#include "Framework.h"
#include "Window.h"

HINSTANCE Window::hInstance = nullptr;
HWND Window::Handle = 0;
std::function<LRESULT(HWND, uint, WPARAM, LPARAM)> Window::InputProc = nullptr;
std::function<LRESULT(HWND, uint, WPARAM, LPARAM)> Window::EditorProc = nullptr;
std::function<void(const uint&, const uint&)> Window::ResizeProc = nullptr;
