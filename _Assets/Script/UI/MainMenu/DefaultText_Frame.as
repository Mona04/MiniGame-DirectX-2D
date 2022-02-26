class DefaultText
{
	Frame@ frame;
	DefaultText(Frame @in_frame)
	{
		@frame = in_frame;
	}

	void Start()
	{
		frame.SetText("응애 \n 나 아기 페페");
	}
	
	void Update()
	{
	}
}