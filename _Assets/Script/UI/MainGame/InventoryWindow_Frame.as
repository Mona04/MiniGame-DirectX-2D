class InventoryTag
{
	Frame@ frame;
	InventoryTag(Frame @in_frame)
	{
		@frame = in_frame;
	}

	void Start()
	{
		frame.SetText("����");
	}

	void Update()
	{
	}
}