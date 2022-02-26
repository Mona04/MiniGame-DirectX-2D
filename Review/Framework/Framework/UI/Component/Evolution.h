#pragma once
#include "IUIWidget.h"

class Evolution : public IUIWidget
{
private:
	friend UI;

private:
	Evolution(class Context* context);
	~Evolution() = default;

	void Clear();

	void Update() override;

	void UpdateTransform();

	void LoadFromFile(const std::string& path) override;
	void SaveToFile(const std::string& path) override;

public:
	void Init_Default();

	void Drag(class Camera* camera = nullptr);

	const Vector3& GetPosition() { return position; }
	void SetPosition(const Vector3& var) { position = var; UpdateTransform(); }

	const Vector2& GetItemScale() { return itemScale; }
	void SetItemScale(const Vector2& var) { itemScale = var; UpdateTransform(); }

	const Vector2& GetItemPadding() { return itemPadding; }
	void SetItemPadding(const Vector2& var) { itemPadding = var; UpdateTransform(); }

	const Vector2& GetTagScale() { return tagScale; }
	void SetTagScale(const Vector2& var) { tagScale = var; UpdateTransform(); }

	const Vector2& GetInfoScale() { return infoScale; }
	void SetInfoScale(const Vector2& var) { infoScale = var; UpdateTransform(); }

	const Vector2& GetInfoPadding() { return infoPadding; }
	void SetInfoPadding(const Vector2& var) { infoPadding = var; UpdateTransform(); }

	const Vector3& GetTipPosition() { return tipPosition; }
	void SetTipPosition(const Vector3& var) { tipPosition = var; UpdateTransform(); }

	const Vector2& GetTipScale() { return tipScale; }
	void SetTipScale(const Vector2& var) { tipScale = var; UpdateTransform(); }

	int GetCoveredItemLoc();

private:
	void UpdateWidthHeight();
	const Vector3 GetBoxPosition(const int& x);

public:
	void UpdateEvolve();
	void UpdateSlots();
	bool IsAbleEvolution(Data_Mob* obj);

private:
	class MouseManager* mouseManager;
	class DataManager* dataManager;
	class GameManager* gameManager;
	class InventoryManager* inventoryManager;

	Vector3 position;
	Vector2 itemScale;
	Vector2 itemPadding;
	Vector2 tagScale;
	Vector2 infoScale;
	Vector2 infoPadding;
	Vector3 tipPosition;
	Vector2 tipScale;
	std::wstring tipText = L"조건에 맞으면 진화할 몬스터가 밝게 있습니다.\n클릭하면 진화합니다.";

	int nSlot;

	float width, height;
};