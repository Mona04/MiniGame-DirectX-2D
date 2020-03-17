#include "Framework.h"
#include "MouseManager.h"

MouseManager::MouseManager(Context* context)
	: ISubsystem(context)
{
	input = context->GetSubsystem<Input>();
	renderer = context->GetSubsystem<Renderer>();
	uiManager = context->GetSubsystem<UIManager>();
	inventoryManager = context->GetSubsystem<InventoryManager>();
	dataManager = context->GetSubsystem<DataManager>();

	EventSystem::Get()->Subscribe(EventType::Default_Update, EVENT_HANDLER(Update));
}

MouseManager::~MouseManager()
{
}

const bool MouseManager::Initialize()
{
	return true;
}

void MouseManager::Update()
{
	UpdateMouse();


	Inventory_ShowItemInfo();
	Inventory_ShowTmpItemImage();
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

void MouseManager::Inventory_ShowItemInfo()
{
	ToolTip* toolTip = uiManager->GetCurrentUI()->GetComponent<ToolTip>();
	if (toolTip == nullptr)
		return;

	Data_Item* itemData =inventoryManager->GetCoveredItem();
	if (itemData == nullptr)
	{
		toolTip->SetIsVisible(false);
		return;
	}

	toolTip->ShowItemInfo(mousePos.x, mousePos.y, itemData);
}

void MouseManager::Inventory_ShowTmpItemImage()
{
	Box* ui = uiManager->GetCurrentUI()->GetComponent<Box>("ItemImage");
	if (ui == nullptr)
		return;

	Data_Item* itemData = inventoryManager->GetTmpItem();
	if (itemData == nullptr)
	{
		ui->SetIsVisible(false);
		return;
	}
	Vector2 itemScale = inventoryManager->GetInventory()->GetItemScale();
	ui->GetFirstFrame()->GetRenderable()->SetTexture(TextureType::Albedo, itemData->_imagePath, itemData->_imagePath);
	ui->GetFirstFrame()->GetTransform()->SetScale(Vector3(itemScale.x * itemData->_sizeX, itemScale.y * itemData->_sizeY, 0));
	ui->GetFirstFrame()->GetTransform()->SetPosition(mousePos);
	ui->SetIsVisible(true);
}

