class DefaultText
{
	Frame@ frame;
	DefaultText(Frame @in_frame)
	{
		@frame = in_frame;
	}

	void Start()
	{
		frame.SetText("사람이 사람처럼 살아야지 \n 안그러냐");
	}

	void Update()
	{
	}
}