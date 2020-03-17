class MainMenuContinue
{
	Frame@ frame;
	MainMenuContinue(Frame @in_frame)
	{
		@frame = in_frame;
	}

	void Start()
	{
		frame.SetText("이어하기");
	}

	void Update()
	{
		int stack = gameManager.MainMenu_GetStack();
		switch(stack)
		{
		case 0:
		{
			frame.SetText("이어하기");
			if(frame.IsClicked() == true)
				gameManager.MainMenu_SetStack(1);
			break;
		}
		case 1:
		{
			frame.SetText("저장 2");
			if(frame.IsClicked() == true)
				gameManager.LoadGame(1);
			break;		
		}
		}

		if(frame.IsCovered() == true)
		{
			uiManager.GetUIComponent_Box("Select").SetVisible(true);
			uiManager.GetUIComponent_Box("Select").SetPosition(frame.GetPosition() - Vector3(0.1f, 0.0f, 0.0f));
		}
	}
}