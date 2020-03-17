class SaveSlot3
{
	Frame@ frame;
	SaveSlot3(Frame @in_frame)
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
			gameManager.SaveGame(2);
		}
	}
}