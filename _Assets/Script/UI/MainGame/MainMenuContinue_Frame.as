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
		if(frame.IsCovered() == true)
		{
			uiManager.GetUIComponent_Box("Select").SetVisible(true);
			uiManager.GetUIComponent_Box("Select").SetPosition(frame.GetPosition() - D3DXVECTOR3(0.1f, 0.0f, 0.0f));
		}
		if(frame.IsClicked() == true)
		{

		}
	}
}