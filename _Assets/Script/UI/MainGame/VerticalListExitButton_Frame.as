class VerticalListExitButton
{
	Frame@ frame;
	VerticalListExitButton(Frame @in_frame)
	{
		@frame = in_frame;
	}

	void Start()
	{
		frame.SetText(" Exit");
	}

	void Update()
	{
	}
}