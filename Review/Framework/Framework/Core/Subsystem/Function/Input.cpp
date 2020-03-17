#include "Framework.h"
#include "Input.h"

Input::Input(Context * context)
	: ISubsystem(context)
	, mousePosition(0, 0), mousePosition_before(0, 0)
	, wheelStatus(0, 0, 0)
	, wheelOldStatus(0, 0, 0)
	, wheelMoveValue(0, 0, 0)
{
	EventSystem::Get()->Subscribe(EventType::Default_Update, EVENT_HANDLER(Update));
}

Input::~Input()
{
}

LRESULT Input::DefaultMouseProc(HWND handle, uint message, WPARAM wParam, LPARAM lParam)
{
	if (message == WM_LBUTTONDOWN || message == WM_MOUSEMOVE)
	{
		mousePosition_before = mousePosition;
		mousePosition.x = static_cast<float>(LOWORD(lParam));	
		mousePosition.y = static_cast<float>(HIWORD(lParam));
	}

	if (message == WM_MOUSEWHEEL)
	{
		short tWheelValue = static_cast<short>(HIWORD(wParam));

		wheelOldStatus.z = wheelStatus.z;
		wheelStatus.z += static_cast<float>(tWheelValue);
	}

	return TRUE;
}

const bool Input::Initialize()
{
	ZeroMemory(keyState, sizeof(keyState));
	ZeroMemory(keyOldState, sizeof(keyOldState));
	ZeroMemory(keyMap, sizeof(keyMap));
	ZeroMemory(buttonStatus, sizeof(byte) * MAX_INPUT_MOUSE);
	ZeroMemory(buttonOldStatus, sizeof(byte) * MAX_INPUT_MOUSE);
	ZeroMemory(buttonMap, sizeof(byte) * MAX_INPUT_MOUSE);
	ZeroMemory(startDblDown, sizeof(DWORD) * MAX_INPUT_MOUSE);
	ZeroMemory(keyCount, sizeof(int) * MAX_INPUT_MOUSE);
	ZeroMemory(startDblClk, sizeof(DWORD) * MAX_INPUT_MOUSE);
	ZeroMemory(buttonCount, sizeof(int) * MAX_INPUT_MOUSE);

	timeDblClk = GetDoubleClickTime();
	startDblClk[0] = GetTickCount();

	for (int i = 1; i < MAX_INPUT_MOUSE; i++)
		startDblClk[i] = startDblClk[0];

	DWORD tLine = 0;
	SystemParametersInfo(SPI_GETWHEELSCROLLLINES, 0, &tLine, 0);

	return true;
}

void Input::Update()
{
	memcpy(keyOldState, keyState, sizeof(keyOldState));

	ZeroMemory(keyState, sizeof(keyState));
	//ZeroMemory(keyMap, sizeof(keyMap));

	GetKeyboardState(keyState);

	for (DWORD i = 0; i < MAX_INPUT_KEY; i++)
	{
		byte key = keyState[i] & 0x80;
		keyState[i] = key ? 1 : 0;

		int oldState = keyOldState[i];
		int state = keyState[i];

		if (keyMap[i] == static_cast<uint>(KeyStatus::KEY_INPUT_STATUS_DBLDOWN))  // press
		{
			if (state == 1)
				keyMap[i] = static_cast<uint>(KeyStatus::KEY_INPUT_STATUS_DBLDOWN);
			else
			{
				if (oldState == 0 && state == 1)
					keyMap[i] = static_cast<uint>(KeyStatus::KEY_INPUT_STATUS_DOWN); //���� 0, ���� 1 - KeyDown
				else if (oldState == 1 && state == 0)
					keyMap[i] = static_cast<uint>(KeyStatus::KEY_INPUT_STATUS_UP); //���� 1, ���� 0 - KeyUp
				else if (oldState == 1 && state == 1)
					keyMap[i] = static_cast<uint>(KeyStatus::KEY_INPUT_STATUS_PRESS); //���� 1, ���� 1 - KeyPress
				else
					keyMap[i] = static_cast<uint>(KeyStatus::KEY_INPUT_STATUS_NONE);
			}
		}
		else if (oldState == 0 && state == 1)
			keyMap[i] = static_cast<uint>(KeyStatus::KEY_INPUT_STATUS_DOWN); //���� 0, ���� 1 - KeyDown
		else if (oldState == 1 && state == 0)
			keyMap[i] = static_cast<uint>(KeyStatus::KEY_INPUT_STATUS_UP); //���� 1, ���� 0 - KeyUp
		else if (oldState == 1 && state == 1)
			keyMap[i] = static_cast<uint>(KeyStatus::KEY_INPUT_STATUS_PRESS); //���� 1, ���� 1 - KeyPress
		else
			keyMap[i] = static_cast<uint>(KeyStatus::KEY_INPUT_STATUS_NONE);
	}

	DWORD tKeyStatus = GetTickCount();
	for (DWORD i = 0; i < MAX_INPUT_KEY; i++)
	{
		if (keyMap[i] == static_cast<uint>(KeyStatus::KEY_INPUT_STATUS_DOWN))
		{
			if (keyCount[i] == 1)
			{
				if ((tKeyStatus - startDblDown[i]) >= timeDblClk)
					keyCount[i] = 0;
				else
					keyMap[i] = static_cast<uint>(KeyStatus::KEY_INPUT_STATUS_DBLDOWN);
			}
			keyCount[i]++;

			if (keyCount[i] == 1)
				startDblDown[i] = tKeyStatus;
		}

		if (keyMap[i] == static_cast<uint>(KeyStatus::KEY_INPUT_STATUS_UP))
		{
			if (keyMap[i] == static_cast<uint>(KeyStatus::KEY_INPUT_STATUS_DBLDOWN))
				keyMap[i] = static_cast<uint>(KeyStatus::KEY_INPUT_STATUS_UP);
			if ((tKeyStatus - startDblDown[i]) >= timeDblClk)
					keyCount[i] = 0;
		}
	}


	memcpy(buttonOldStatus, buttonStatus, sizeof(byte) * MAX_INPUT_MOUSE);

	ZeroMemory(buttonStatus, sizeof(byte) * MAX_INPUT_MOUSE);
	ZeroMemory(buttonMap, sizeof(byte) * MAX_INPUT_MOUSE);

	buttonStatus[0] = GetAsyncKeyState(VK_LBUTTON) & 0x8000 ? 1 : 0;
	buttonStatus[1] = GetAsyncKeyState(VK_RBUTTON) & 0x8000 ? 1 : 0;
	buttonStatus[2] = GetAsyncKeyState(VK_MBUTTON) & 0x8000 ? 1 : 0;

	for (DWORD i = 0; i < MAX_INPUT_MOUSE; i++)
	{
		int tOldStatus = buttonOldStatus[i];
		int tStatus = buttonStatus[i];

		if (tOldStatus == 0 && tStatus == 1)
			buttonMap[i] = static_cast<uint>(ButtonStatus::BUTTON_INPUT_STATUS_DOWN);
		else if (tOldStatus == 1 && tStatus == 0)
			buttonMap[i] = static_cast<uint>(ButtonStatus::BUTTON_INPUT_STATUS_UP);
		else if (tOldStatus == 1 && tStatus == 1)
			buttonMap[i] = static_cast<uint>(ButtonStatus::BUTTON_INPUT_STATUS_PRESS);
		else
			buttonMap[i] = static_cast<uint>(ButtonStatus::BUTTON_INPUT_STATUS_NONE);
	}

	POINT point = { 0, 0 };
	GetCursorPos(&point);
	ScreenToClient(Setting::Get()->GetWindowHandle(), &point);

	wheelOldStatus.x = wheelStatus.x;
	wheelOldStatus.y = wheelStatus.y;

	wheelStatus.x = static_cast<float>(point.x);
	wheelStatus.y = static_cast<float>(point.y);

	wheelMoveValue = wheelStatus - wheelOldStatus;
	wheelOldStatus.z = wheelStatus.z;

	DWORD tButtonStatus = GetTickCount();
	for (DWORD i = 0; i < MAX_INPUT_MOUSE; i++)
	{
		if (buttonMap[i] == static_cast<uint>(ButtonStatus::BUTTON_INPUT_STATUS_DOWN))
		{
			if (buttonCount[i] == 1)
			{
				if ((tButtonStatus - startDblClk[i]) >= timeDblClk)
					buttonCount[i] = 0;
			}
			buttonCount[i]++;

			if (buttonCount[i] == 1)
				startDblClk[i] = tButtonStatus;
		}

		if (buttonMap[i] == static_cast<uint>(ButtonStatus::BUTTON_INPUT_STATUS_UP))
		{
			if (buttonCount[i] == 1)
			{
				if ((tButtonStatus - startDblClk[i]) >= timeDblClk)
					buttonCount[i] = 0;
			}
			else if (buttonCount[i] == 2)
			{
				if ((tButtonStatus - startDblClk[i]) <= timeDblClk)
					buttonMap[i] = static_cast<uint>(ButtonStatus::BUTTON_INPUT_STATUS_DBLCLK);

				buttonCount[i] = 0;
			}
		}
	}
}