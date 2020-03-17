class NormalEnding
{
	Frame@ frame;
	NormalEnding(Frame @in_frame)
	{
		@frame = in_frame;
	}

	void Start()
	{
		frame.SetText("모리안은 로스트아크 세계의 문을 열었다.... \n노말엔딩. \n좀 있으면 메인화면으로 감.");
	}

	void Update()
	{
	}
}