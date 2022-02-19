#include "stdafx.h"
#include "Engine.h"
#include "Subsystem/ResourceManager.h"
#include "Subsystem/Timer.h"
#include "ImageEditor/ImageEditor.h"


Engine::Engine()
	: context(nullptr)
	, imageEditor(nullptr)
	, hWnd(0)
	, hInstance(0)
	, input("")
{
}

Engine::~Engine()
{
	SAFE_DELETE(context);
}

void Engine::Initialize()
{
	context = new Context();
	context->RegisterSubsystem<ResourceManager>();
	context->RegisterSubsystem<Timer>();

	imageEditor = new ImageEditor(context);

	hWnd = Setting::Get()->GetHWND();
	hInstance = Setting::Get()->GetHInstance();

	input = "";

	Create();
}

void Engine::Update()
{
	context->GetSubsystem<Timer>()->Update();
	imageEditor->Update();
}

void Engine::Create()
{
	CreateWindowW(TEXT("button"), TEXT("Load All"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 10, 20, 100, 25, hWnd, (HMENU)0, hInstance, NULL);
	CreateWindowW(TEXT("button"), TEXT("Animate"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 120, 20, 100, 25, hWnd, (HMENU)1, hInstance, NULL);
	CreateWindowW(TEXT("button"), TEXT("Image Path"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 230, 20, 100, 25, hWnd, (HMENU)2, hInstance, NULL);
	CreateWindowW(TEXT("button"), TEXT("Info Path"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 230, 50, 100, 25, hWnd, (HMENU)3, hInstance, NULL);
}

void Engine::Command(WPARAM wParam)
{
	switch (LOWORD(wParam))
	{
	case 0:
	{
		FileSystem::OpenFileDialog([this](const std::string& path) {imageEditor->LoadImages(FileSystem::GetDirectoryFromPath(path)); }, "Supported Files(*.png)\0*.png", (FileSystem::GetWorkingDirectory()+"../").c_str());
		break;
	}
	case 1:
		FileSystem::OpenFileDialog([this](const std::string& path) { imageEditor->LoadFrames(path); }, "Supported Files(*.png)\0*.png", (FileSystem::GetWorkingDirectory() + "../").c_str());
		InvalidateRect(hWnd, nullptr, false);
		break;
	case 2:
		FileSystem::OpenFilePathDialog([this](const std::string& path) { imageEditor->SetImageFileSavePath(path + "//"); }, "*.*", (FileSystem::GetWorkingDirectory() + "../").c_str());
		break;
	case 3:
		FileSystem::OpenFilePathDialog([this](const std::string& path) { imageEditor->SetInfoFileSavePath(path + "//"); }, "*.*", (FileSystem::GetWorkingDirectory() + "../").c_str());
		break;
	}
}

void Engine::Paint(HDC hdc)
{
	TextOutA(hdc, 100, 100, input.c_str(), input.length());

	imageEditor->ShowFrames(hdc);		
}

void Engine::Typing(WPARAM wParam)
{
	input += (TCHAR)wParam;
	InvalidateRect(hWnd, NULL, FALSE);
}
