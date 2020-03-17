class MainMenuStart
{
	Frame@ frame;
	MainMenuStart(Frame @in_frame)
	{
		@frame = in_frame;
	}

	void Start()
	{
		frame.SetText("시작하기");
	}

	void Update()
	{
		int stack = gameManager.MainMenu_GetStack();
		switch(stack)
		{
		case 0:
		{
			frame.SetText("시작하기");
			if(frame.IsClicked() == true)
				gameManager.MainMenu_Start();
			break;
		}
		case 1:
		{
			frame.SetText("저장 1");
			if(frame.IsClicked() == true)
				gameManager.LoadGame(0);
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