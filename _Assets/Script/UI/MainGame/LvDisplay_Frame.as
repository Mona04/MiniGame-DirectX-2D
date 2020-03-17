class LvDisplay
{
	Frame@ frame;
	LvDisplay(Frame @in_frame)
	{
		@frame = in_frame;
	}

	void Start()
	{
		frame.SetText("0");
	}

	void Update()
	{
		frame.SetText("Lv" + gameManager.GetProtagonistLv());
	}
}