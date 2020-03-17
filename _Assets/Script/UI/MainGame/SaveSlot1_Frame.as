class SaveSlot1
{
	Frame@ frame;
	SaveSlot1(Frame @in_frame)
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
			gameManager.SaveGame(0);
		}
	}
}