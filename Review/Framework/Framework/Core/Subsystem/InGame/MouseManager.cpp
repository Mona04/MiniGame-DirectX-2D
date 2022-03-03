#include "Framework.h"
#include "MouseManager.h"

MouseManager::MouseManager(Context* context)
	: ISubsystem(context)
{
	EventSystem::Get()->Subscribe(EventType::Default_Update, EVENT_HANDLER(Update));
}

MouseManager::~MouseManager()
{
}

const bool MouseManager::Initialize()
{
	input = context->GetSubsystem<Input>();
	renderer = context->GetSubsystem<Renderer>();
	uiManager = context->GetSubsystem<UIManager>();
	inventoryManager = context->GetSubsystem<InventoryManager>();
	dataManager = context->GetSubsystem<DataManager>();

	return true;
}

void MouseManager::Update()
{
	UpdateMouse();
}

void MouseManager::UpdateMouse()
{
	Vector2 resolution = renderer->GetResolution();
	Vector2 curPos = input->GetMousePosition();

	mousePos = Vector3(curPos.x, curPos.y, 0.0f);
	mousePos.x = 2.0f * mousePos.x / resolution.x - 1.0f;
	mousePos.y = -2.0f * mousePos.y / resolution.y + 1.0f;
	mousePos.z = 0;

	Vector2 moveValue = input->GetMouseMoveVaule();
	moveValue.x = 2.0f * moveValue.x / resolution.x;
	moveValue.y = -2.0f * moveValue.y / resolution.y;
	mouseMoveVector = Vector3(moveValue.x, moveValue.y, 0);

	isClicked = input->BtnDown(KeyCode::CLICK_LEFT);
	isDblClicked = input->BtnDoubleClick(KeyCode::CLICK_LEFT);
	isDragged = input->BtnPress(KeyCode::CLICK_LEFT);
}
