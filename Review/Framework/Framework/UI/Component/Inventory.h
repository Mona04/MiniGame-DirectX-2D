#pragma once
#include "IUIWidget.h"

class Inventory : public IUIWidget
{
private:
	friend UI;

private:
	Inventory(class Context* context);
	~Inventory() = default;

	void Clear();
	
	void Update() override;

	void UpdateTransform();

	void LoadFromFile(const std::string& path) override;
	void SaveToFile(const std::string& path) override;

public:
	void Init_Default();

	void Clear_Items();

	void Drag(class Camera* camera = nullptr);

	int& GetMaxX() { return maxX; }
	void SetMaxX(const int& x) { maxX = x; }

	int& GetMaxY() { return maxY; }
	void SetMaxY(const int& y) { maxY = y; }

	const Vector3& GetPosition() { return position; }
	void SetPosition(const Vector3& var) { position = var; UpdateTransform();}

	const Vector2& GetItemScale() { return itemScale; }
	void SetItemScale(const Vector2& var) { itemScale = var; UpdateTransform();}

	const Vector2& GetItemPadding() { return itemPadding; }
	void SetItemPadding(const Vector2& var) { itemPadding = var; UpdateTransform();}

	const Vector2& GetTagScale() { return tagScale; }
	void SetTagScale(const Vector2& var) { tagScale = var; UpdateTransform();}

	const Vector2& GetAmountScale() { return amountScale; }
	void SetAmountScale(const Vector2& var) { amountScale = var; UpdateTransform(); }

	const Vector2& GetAmountPadding() { return amountPadding; }
	void SetAmountPadding(const Vector2& var) { amountPadding = var; UpdateTransform(); }

	bool InsertItem(const int& x, const int& y, const class Data_Item* itemData, const uint& leftAmount);
	void DeleteItem(const int& x, const int& y, const uint& leftAmount);
	void DeleteItemAll(const int& x, const int& y);

	int2 GetCoveredItemLoc();

private:
	void UpdateWidthHeight();
	const Vector3 GetBoxPosition(const int& x, const int& y);

private:
	class MouseManager* mouseManager;

	Vector3 position;
	Vector2 itemScale;
	Vector2 itemPadding;
	Vector2 tagScale;
	Vector2 amountScale;
	Vector2 amountPadding;

	int maxX, maxY;

	float width, height;
};