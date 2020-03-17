class ButtonContinue
{
	Frame@ frame;
	ButtonContinue(Frame @in_frame)
	{
		@frame = in_frame;
	}

	void Start()
	{
		frame.SetText("계속하기");
	}

	void Update()
	{
	}
}