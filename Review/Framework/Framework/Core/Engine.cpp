#include "Framework.h"
#include "Engine.h"
#include <random>

ulong Engine::engineFlags;

Engine::Engine()
{
	context = new Context();
	context->RegisterSubsystem<Thread>();          // 해제가 생성 순서가 아니라서 먼저 해야지 에러 안 뜸
	context->RegisterSubsystem<Graphics>();
	timer = context->RegisterSubsystem<Timer>();
	context->RegisterSubsystem<Input>();
	context->RegisterSubsystem<ResourceManager>();
	context->RegisterSubsystem<Audio>();
	context->RegisterSubsystem<DataManager>();
	context->RegisterSubsystem<ScriptManager>();  // 먼저 안하면 UI 에서 scripter 소환해서 ㅈ됨
	context->RegisterSubsystem<SceneManager>();
	context->RegisterSubsystem<PhysicsManager>();
	context->RegisterSubsystem<UIManager>();
	context->RegisterSubsystem<Renderer>();

	context->RegisterSubsystem<DialogManager>();  // Managers below are inGame Manager
	context->RegisterSubsystem<InventoryManager>();
	context->RegisterSubsystem<MonsterManager>();
	context->RegisterSubsystem<GameManager>();  // Init InventoryManager
	context->RegisterSubsystem<MouseManager>();  // use initialize inventoryManager ex
	context->RegisterSubsystem<ExtraManager>(); 

	context->InitializeSubsystems();

	frame = new UI_Component_Frame(context);
	frame->GetRenderable()->SetMesh("SCREEN_QUAD.mesh", "screen");
	frame->GetRenderable()->SetMaterial("UI/UI_Default.material", "UI_Default");

	context->GetSubsystem<Renderer>()->SetResolution(
		Vector2(
			static_cast<float>(Setting::Get()->GetWidth()),
			static_cast<float>(Setting::Get()->GetHeight())
		)); // 엔진 플래그 생성시 되는걸로 바꿔야함

	frame->Update();
}

Engine::~Engine()
{
	SAFE_DELETE(context);
	SAFE_DELETE(frame);
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
