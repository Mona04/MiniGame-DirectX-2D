class Ex
{
	Text@ text;
	Ex(Text @in_text)
	{
		@text = in_text;
	}

	void Start()
	{
		text.SetText("그건 없는 거지");
	}

	void Update()
	{
	}
}