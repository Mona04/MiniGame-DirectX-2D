class MainMenuExit
{
	Frame@ frame;
	MainMenuExit(Frame @in_frame)
	{
		@frame = in_frame;
	}

	void Start()
	{
		frame.SetText("나가기");
	}

	void Update()
	{
		int stack = gameManager.MainMenu_GetStack();

		if(frame.IsCovered() == true)
		{
			uiManager.GetUIComponent_Box("Select").SetVisible(true);
			uiManager.GetUIComponent_Box("Select").SetPosition(frame.GetPosition() - Vector3(0.1f, 0.0f, 0.0f));
		}

		switch(stack)
		{
		case 0:
		{
			frame.SetText("나가기");
			if(frame.IsClicked() == true)
				gameManager.MainMenu_Exit();
			break;
		}
		case 1:
		{
			frame.SetText("저장 3");
			if(frame.IsClicked() == true)
				gameManager.LoadGame(2);
			break;		
		}
		}
	}
}