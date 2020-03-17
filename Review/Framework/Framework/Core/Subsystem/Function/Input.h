#pragma once
#include "../ISubsystem.h"

#define MAX_INPUT_KEY 255
#define MAX_INPUT_MOUSE 8

enum KeyCode : DWORD
{
	CLICK_LEFT = 0x00,
	CLICK_RIGHT = 0x01,

	KEY_LEFT = 0x25,
	KEY_UP = 0x26,
	KEY_RIGHT = 0x27,
	KEY_DOWN = 0x28,

	KEY_0 = 0x30,
	KEY_1 = 0x31,
	KEY_2 = 0x32,
	KEY_3 = 0x33,
	KEY_4 = 0x34,
	KEY_5 = 0x35,
	KEY_6 = 0x36,
	KEY_7 = 0x37,
	KEY_8 = 0x38,
	KEY_9 = 0x39,
	KEY_A = 0x41,
	KEY_B = 0x42,
	KEY_C = 0x43,
	KEY_D = 0x44,
	KEY_E = 0x45,
	KEY_F = 0x46,
	KEY_G = 0x47,
	KEY_H = 0x48,
	KEY_I = 0x49,
	KEY_J = 0x4A,
	KEY_K = 0x4B,
	KEY_L = 0x4C,
	KEY_M = 0x4D,
	KEY_N = 0x4E,
	KEY_O = 0x4F,
	KEY_P = 0x50,
	KEY_Q = 0x51,
	KEY_R = 0x52,
	KEY_S = 0x53,
	KEY_T = 0x54,
	KEY_U = 0x55,
	KEY_V = 0x56,
	KEY_W = 0x57,
	KEY_X = 0x58,
	KEY_Y = 0x59,
	KEY_Z = 0x5A,
	KEY_SHIFT = 0x10,
	KEY_CONTROL = 0x11,
	KEY_SPACE = 0x20
};

class Input : public ISubsystem
{
public:
	Input(class Context* context);
	virtual ~Input();

	const Vector3& GetWheelMoveValue() const { return wheelMoveValue; }
	const Vector2& GetMousePosition() const { return mousePosition; }
	const Vector2& GetMouseMoveVaule() const { return mousePosition - mousePosition_before; }

	void SetMousePosition(const Vector2& pos) { mousePosition = pos; }
	void SetMousePosition_Before(const Vector2& pos) { if(pos != mousePosition_before) mousePosition_before = pos; }
	
	void SetWheelOldStatus(const Vector3& var) { wheelOldStatus = var; }
	Vector3 GetWheelStatus() { return wheelStatus; }
	void SetWheelStatus(const Vector3& var) { wheelStatus = var; }
	
	LRESULT DefaultMouseProc(HWND, uint, WPARAM, LPARAM);

	const bool Initialize() override;
	void Update();

	const bool BtnDown(const DWORD& button) const { return buttonMap[button] == static_cast<uint>(ButtonStatus::BUTTON_INPUT_STATUS_DOWN); }
	const bool BtnUp(const DWORD& button) const { return buttonMap[button] == static_cast<uint>(ButtonStatus::BUTTON_INPUT_STATUS_UP); }
	const bool BtnPress(const DWORD& button) const { return buttonMap[button] == static_cast<uint>(ButtonStatus::BUTTON_INPUT_STATUS_PRESS); }
	const bool BtnDoubleClick(const DWORD& button) const { return buttonMap[button] == static_cast<uint>(ButtonStatus::BUTTON_INPUT_STATUS_DBLCLK); }

	const bool KeyDown(const DWORD& key) const { return keyMap[key] == static_cast<uint>(KeyStatus::KEY_INPUT_STATUS_DOWN); }
	const bool KeyUp(const DWORD& key) const { return keyMap[key] == static_cast<uint>(KeyStatus::KEY_INPUT_STATUS_UP); }
	const bool KeyPress(const DWORD& key) const { return keyMap[key] == static_cast<uint>(KeyStatus::KEY_INPUT_STATUS_PRESS); }
	const bool KeyDoubleDown(const DWORD& key) const { return keyMap[key] == static_cast<uint>(KeyStatus::KEY_INPUT_STATUS_DBLDOWN); }

private:
	enum class MouseRotationState
	{
		MOUSE_ROTATION_NONE = 0,
		MOUSE_ROTATION_LEFT,
		MOUSE_ROTATION_RIGHT
	};

	enum class ButtonStatus
	{
		BUTTON_INPUT_STATUS_NONE = 0,
		BUTTON_INPUT_STATUS_DOWN,
		BUTTON_INPUT_STATUS_UP,
		BUTTON_INPUT_STATUS_PRESS,
		BUTTON_INPUT_STATUS_DBLCLK
	};

	enum class KeyStatus
	{
		KEY_INPUT_STATUS_NONE = 0,
		KEY_INPUT_STATUS_DOWN,
		KEY_INPUT_STATUS_UP,
		KEY_INPUT_STATUS_PRESS,
		KEY_INPUT_STATUS_DBLDOWN,
	};

private:
	byte keyState[MAX_INPUT_KEY];
	byte keyOldState[MAX_INPUT_KEY];
	byte keyMap[MAX_INPUT_KEY];
	byte buttonStatus[MAX_INPUT_MOUSE];
	byte buttonOldStatus[MAX_INPUT_MOUSE];
	byte buttonMap[MAX_INPUT_MOUSE];
	
	DWORD startDblDown[MAX_INPUT_KEY];
	int keyCount[MAX_INPUT_KEY];
	DWORD startDblClk[MAX_INPUT_MOUSE];
	int buttonCount[MAX_INPUT_MOUSE];
	DWORD timeDblClk;
	
	Vector2 mousePosition; //마우스 위치
	Vector2 mousePosition_before;
	Vector3 wheelStatus;
	Vector3 wheelOldStatus;
	Vector3 wheelMoveValue;
};