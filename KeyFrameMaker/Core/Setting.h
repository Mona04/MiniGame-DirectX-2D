#pragma once
#include "stdafx.h"

class Setting final
{
public:
	static Setting* Get() { static Setting instance; return &instance; }

private:
	Setting() = default;
	~Setting() = default;

public:
	HINSTANCE GetHInstance() { return hInstance; }
	void SetHInstance(HINSTANCE hInstance) { this->hInstance = hInstance; }

	HWND GetHWND() { return hHandle; }
	void SetHWND(HWND hHandle) { this->hHandle = hHandle; }

	uint GetWidth() { return width; }
	void SetWidth(const uint& width) { this->width = width; }

	uint GetHeight() { return height; }
	void SetHeight(const uint& height) { this->height = height; }

private:
	HINSTANCE hInstance;
	HWND hHandle;
	uint width;
	uint height;
};
