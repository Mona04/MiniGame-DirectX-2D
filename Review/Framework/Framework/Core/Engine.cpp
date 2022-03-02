#include "Framework.h"
#include "Engine.h"
#include <random>

ulong Engine::engineFlags;

Engine::Engine()
{
}

Engine::~Engine()
{
	context->UnregistSubsystem<Thread>();
	context->UnregistSubsystem<GameManager>();
	context->UnregistSubsystem<UIManager>();
	context->UnregistSubsystem<SceneManager>();
	context->UnregistSubsystem<ResourceManager>();
	context->UnregistSubsystem<DataManager>();
	context->UnregistSubsystem<ScriptManager>();

	SAFE_DELETE(context);
	SAFE_DELETE(frame);
}

void Engine::Initialize()
{
	context = new Context(this);

	timer = context->RegistSubsystem<Timer>();
	context->RegistSubsystem<Thread>();
	context->RegistSubsystem<Graphics>();
	context->RegistSubsystem<Input>();
	context->RegistSubsystem<PhysicsManager>();
	context->RegistSubsystem<ResourceManager>();
	context->RegistSubsystem<Audio>();
	context->RegistSubsystem<DataManager>();
	context->RegistSubsystem<ScriptManager>();  // 먼저 안하면 UI 에서 scripter 소환해서 안됨
	context->RegistSubsystem<SceneManager>();
	context->RegistSubsystem<UIManager>();
	context->RegistSubsystem<Renderer>();

	context->RegistSubsystem<DialogManager>();
	context->RegistSubsystem<InventoryManager>();
	context->RegistSubsystem<MonsterManager>();  // Renderer Update 이후에 되야함

	context->RegistSubsystem<GameManager>();  // Init InventoryManager
	context->RegistSubsystem<MouseManager>();  // use initialize inventoryManager ex
	context->RegistSubsystem<ExtraManager>();


	context->InitializeSubsystems();

	// Main Render Frame
	frame = new UIWidgetFrame(context);
	frame->GetRenderable()->SetMesh("SCREEN_QUAD.mesh", "screen");
	frame->GetRenderable()->SetMaterial("UI/UI_Default.material", "UI_Default");

	context->GetSubsystem<Renderer>()->SetResolution(
		Vector2(
			static_cast<float>(Setting::Get()->GetWidth()),
			static_cast<float>(Setting::Get()->GetHeight())
		)); // 엔진 플래그 생성시 되는걸로 바꿔야함

	frame->Update();
}

void Engine::Update()
{
	updateEnd = false;

	frame->Update();
	timer->Update();

	if (!timer->IsUpdatedFPS())
		return;

	if (IsOnEngineFlags(ENGINEFLAGS_UPDATE))
		EventSystem::Get()->Fire(EventType::Default_Update);
	
	if (IsOnEngineFlags(ENGINEFLAGS_UPDATE) && IsOnEngineFlags(ENGINEFLAGS_PLAY) && !ProgressReport::Get()->GetIsLoadingOfReport(ProgressReport::Scene))
		EventSystem::Get()->Fire(EventType::Update);

	if (IsOnEngineFlags(ENGINEFLAGS_RENDER))
		EventSystem::Get()->Fire(EventType::Render);

	if (IsOnEngineFlags(ENGINEFLAGS_GAME))
		Render();

	updateEnd = true;
	if (bDestroy)
	{
		Window::Destroy();
	}
}

void Engine::Render()
{
	context->GetSubsystem<Renderer>()->RenderForEngine(frame);
}

void Engine::Resize(const uint& width, const uint& height)
{
	Setting::Get()->SetWidth(width);
	Setting::Get()->SetHeight(height);

	context->GetSubsystem<Renderer>()->SetResolution(
		Vector2(
			static_cast<float>(Setting::Get()->GetWidth()),
			static_cast<float>(Setting::Get()->GetHeight())
		)); // 엔진 플래그 생성시 되는걸로 바꿔야함
	
	frame->Update();
}
