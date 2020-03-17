class VerticalListSaveButton
{
	Frame@ frame;
	VerticalListSaveButton(Frame @in_frame)
	{
		@frame = in_frame;
	}

	void Start()
	{
		frame.SetText("Save");
	}

	void Update()
	{
	}
}