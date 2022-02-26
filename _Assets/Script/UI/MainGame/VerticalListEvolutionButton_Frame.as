class VerticalListEvolutionButton
{
	Frame@ frame;
	VerticalListEvolutionButton(Frame @in_frame)
	{
		@frame = in_frame;
	}

	void Start()
	{
		frame.SetText(" Evol");
	}
	
	void Update()
	{
		if(frame.IsClicked())
			monsterManager.ToggleEvolution();
	}
}