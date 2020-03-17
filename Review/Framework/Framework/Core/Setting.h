#pragma once
#include "Framework.h"

class Setting
{
public:
	static Setting* Get()
	{
		static Setting Instance;
		return &Instance;
	}

	HINSTANCE GetWindowInstance() const { return hInstance; }
	HWND GetWindowHandle() const { return handle; }
	const uint& GetWidth() const { return width; }
	const uint& GetHeight() const { return height; }
	const bool& IsVsync() const { return bVsync; }

	void SetWindowInstance(HINSTANCE hInstance) { this->hInstance = hInstance; }
	void SetWindowHandle(HWND handle) { this->handle = handle; }
	void SetWidth(const uint& width) { this->width = width; }
	void SetHeight(const uint& height) { this->height = height; }
	void SetIsVsync(const bool& bVsync) { this->bVsync = bVsync; }

private:
	Setting()
		: hInstance(nullptr)
		, handle(nullptr)
		, width(0)
		, height(0)
		, bVsync(true)
	{}

private:
	HINSTANCE hInstance;
	HWND handle;
	uint width;
	uint height;
	bool bVsync;
};