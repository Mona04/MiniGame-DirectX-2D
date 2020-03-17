class SaveSlot2
{
	Frame@ frame;
	SaveSlot2(Frame @in_frame)
	{
		@frame = in_frame;
	}

	void Start()
	{
	}

	void Update()
	{
		if(frame.IsClicked() == true)
		{
			gameManager.SaveGame(1);
		}
	}
}