class EvolutionTag
{
	Frame@ frame;
	EvolutionTag(Frame @in_frame)
	{
		@frame = in_frame;
	}

	void Start()
	{
		frame.SetText("��ȭ");
	}

	void Update()
	{
	}
}