class DefaultText
{
	Frame@ frame;
	DefaultText(Frame @in_frame)
	{
		@frame = in_frame;
	}

	void Start()
	{
		frame.SetText("����� ���ó�� ��ƾ��� \n �ȱ׷���");
	}

	void Update()
	{
	}
}