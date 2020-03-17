class DefaultTextName
{
	Frame@ frame;
	DefaultTextName(Frame @in_frame)
	{
		@frame = in_frame;
	}

	void Start()
	{
		frame.SetText("¸ð¸®¾È");
	}

	void Update()
	{
	}
}