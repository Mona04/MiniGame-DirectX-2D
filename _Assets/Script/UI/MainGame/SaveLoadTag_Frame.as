class SaveLoadTag
{
	Frame@ frame;
	SaveLoadTag(Frame @in_frame)
	{
		@frame = in_frame;
	}

	void Start()
	{
		frame.SetText("����");
	}

	void Update()
	{
	}
}