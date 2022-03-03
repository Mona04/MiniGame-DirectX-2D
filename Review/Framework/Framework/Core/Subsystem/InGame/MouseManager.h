#pragma once
#include "../ISubsystem.h"

class MouseManager final : public ISubsystem
{
public:
	MouseManager(class Context* context);
	~MouseManager();

	const bool Initialize() override;
	void Update();

private:
	void UpdateMouse();

public:
	const Vector3& GetMousePos() const { return mousePos; }
	const Vector3& GetMouseMoveVector() const { return mouseMoveVector;}
	const bool IsClicked() { return isClicked; }
	const bool IsDblClicked() { return isDblClicked; }
	const bool IsDragged() { return isDragged; }

private:
	class Input* input;
	class Renderer* renderer;
	class UIManager* uiManager;
	class DataManager* dataManager;
	class InventoryManager* inventoryManager;

	Vector3 mousePos = Vector3(0, 0, 0);
	Vector3 mouseMoveVector = Vector3(0, 0, 0);
	bool isClicked = false;
	bool isDblClicked = false;
	bool isDragged = false;
};