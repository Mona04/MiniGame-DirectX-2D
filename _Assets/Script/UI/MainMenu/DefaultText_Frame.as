class DefaultText
{
	Frame@ frame;
	DefaultText(Frame @in_frame)
	{
		@frame = in_frame;
	}

	void Start()
	{
		frame.SetText("���� \n �� �Ʊ� ����");
	}
	
	void Update()
	{
	}
}